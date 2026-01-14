/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:02:27 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/14 13:41:01 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

scop::scop(char *filename) {
	this->_centerDefine = false;
	if (isDirectory(filename))
		throw std::runtime_error("Can't open a directory as a file");

	int len = strlen(filename);
	if (len < 4 || strncmp(&filename[len - 4], ".obj", 4) != 0)
		throw std::runtime_error("Can't open a non .obj file");

	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Can't open file");

	str	line;
	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r')
			line.pop_back();

		if (line.empty() || line[0] == '#')
			continue;

		std::istringstream iss(line);
		str type;
		iss >> type;
		str data;
		std::getline(iss, data);
		data.erase(0, data.find_first_not_of(" \t"));

		if (type == "mtllib")
			setMaterialFilename(data, filename);
		else if (type == "o")
			setName(data);
		else if (type == "s") {
			if (data == "off")
				setSmooth(0);
			else if (data == "on")
				setSmooth(1);
			else
				setSmooth(std::atoi(data.c_str()));
		}
		else if (type == "v")
			addVerticesPos(data);
		else if (type == "vn")
			addVerticesNormal(data);
		else if (type == "vt")
			addVerticesText(data);
		else if (type == "f")
			addIndices(data);
		else if (type == "usemtl")
			setUsemtl(data);
	}

	if (this->_usemtl.empty()) {
		Material	current = Material();
		
		current.texture.LoadImage("./resources/img/mylittleponey.bmp");
		current.id = 0;
		this->_usemtl.insert({"", current});
		makeTexArray();
	}

	file.close();
}


scop::~scop() {}

void	scop::setMaterialFilename(str newMaterialFilename, char *filename) {
	newMaterialFilename.erase(
		std::remove_if(newMaterialFilename.begin(), newMaterialFilename.end(), [](unsigned char c){ return c == '\r' || c == ' ' || c == '\t'; }),
		newMaterialFilename.end()
	);
	this->_materialFilename = newMaterialFilename;

	str		fileDir = filename;
	size_t	endOfSuffix = fileDir.find_last_of('/');

	if (endOfSuffix != str::npos)
		fileDir = fileDir.substr(0, endOfSuffix + 1);
	else
		fileDir.clear();
	str	mtlDir = fileDir + newMaterialFilename;

	parseMtl(mtlDir, fileDir);
	makeTexArray();
}

void	scop::setName(str newName) {
	this->_name = newName;
}

void	scop::setUsemtl(str newUsemtl) {
	this->id = this->_usemtl[newUsemtl].id;
}

void	scop::setSmooth(int newSmooth) {
	this->_smooth = newSmooth;
}


void	scop::addVerticesPos(str newVertices) {
	std::vector<str>	values = split(newVertices, " ");
	GLfloat				v1, v2, v3;

	if (values.size() < 3)
		throw std::runtime_error(str("Not the right number of Vertices for Position"));

	v1 = static_cast<GLfloat>(std::stod(values[0].c_str()));
	v2 = static_cast<GLfloat>(std::stod(values[1].c_str()));
	v3 = static_cast<GLfloat>(std::stod(values[2].c_str()));

	glm::vec3	pos(v1, v2, v3);

	this->_verticesPos.push_back(pos);
}

void	scop::addVerticesNormal(str newVertices) {
	std::vector<str>	values = split(newVertices, " ");
	GLfloat				v1, v2, v3;

	if (values.size() < 3)
		throw std::runtime_error(str("Not the right number of Vertices for Normal"));

	v1 = static_cast<GLfloat>(std::stod(values[0].c_str()));
	v2 = static_cast<GLfloat>(std::stod(values[1].c_str()));
	v3 = static_cast<GLfloat>(std::stod(values[2].c_str()));

	glm::vec3	pos(v1, v2, v3);

	this->_verticesNormal.push_back(pos);
}

void	scop::addVerticesText(str newVertices) {
	std::vector<str>	values = split(newVertices, " ");
	GLfloat				v1, v2;

	if (values.size() < 2)
		throw std::runtime_error(str("Not the right number of Vertices for Texture"));

	v1 = static_cast<GLfloat>(std::stod(values[0].c_str()));
	v2 = static_cast<GLfloat>(std::stod(values[1].c_str()));

	vec2	pos(v1, v2);

	this->_verticesText.push_back(pos);
}

void	scop::addIndices(str newIndices) {
	std::vector<str>	values = split(newIndices, " ");
	glm::vec3			v1, v2, v3, v4;
	
	if (values.size() == 3) {
		
		v1 = parseIndices(values[0]);
		v2 = parseIndices(values[1]);
		v3 = parseIndices(values[2]);
		
		normalizeVector(v1, v2, v3);
	}
	else if (values.size() == 4) {
		
		v1 = parseIndices(values[0]);
		v2 = parseIndices(values[1]);
		v3 = parseIndices(values[2]);
		
		normalizeVector(v1, v2, v3);
		
		v1 = parseIndices(values[0]);
		v3 = parseIndices(values[2]);
		v4 = parseIndices(values[3]);
		
		normalizeVector(v1, v3, v4);
	}
	else
		throw std::runtime_error("Not the right number of Indices");
}

glm::vec3	scop::parseIndices(str indice) {
	if (!_centerDefine) {
		computeBoundingBox();
		_centerDefine = true;
	}

	std::vector<str>	values = split(indice, "/");
	
	for (size_t i = 0; i < values.size(); ++i)
		values[i] = trim(values[i]);

	if (values.size() == 1) {
		if (!isCorrectDigit(values[0]))
			throw std::runtime_error("Vertex index isn't a number");
		GLuint	v = std::atoi(values[0].c_str()) - 1;
		_indices.push_back(v);

		glm::vec3	ret(v, -999, -999);
		return (ret);
	}

	if (values.size() >= 2) {
		GLuint		v = -999, vt = -999, vn = -999;
		
		if (!values[0].empty()) {
			if (!isCorrectDigit(values[0]))
				throw std::runtime_error("Vertex index isn't a number");
			v = std::atoi(values[0].c_str()) - 1;
			_indices.push_back(v);
	}
	if (values.size() > 1 && !values[1].empty()) {
		if (!isCorrectDigit(values[1]))
			throw std::runtime_error("Texture index isn't a number");
		vt = std::atoi(values[1].c_str()) - 1;
		_indicesText.push_back(vt);
	}
	if (values.size() > 2 && !values[2].empty()) {
		if (!isCorrectDigit(values[2]))
			throw std::runtime_error("Normal index isn't a number");
		vn = std::atoi(values[2].c_str()) - 1;
		_indicesNormal.push_back(vn);
	}
	glm::vec3	ret(v, vt, vn);
	return (ret);
}

throw std::runtime_error("Invalid face indices format");
}

void scop::normalizeVector(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
	glm::vec3 normal = glm::normalize(glm::cross(
		_verticesPos[B.x] - _verticesPos[A.x],
		_verticesPos[C.x] - _verticesPos[A.x]
	));

	glm::vec3 positions[3] = {
		_verticesPos[A.x],
		_verticesPos[B.x],
		_verticesPos[C.x]
	};

	vec2 uvs[3];
	for (int i = 0; i < 3; ++i) {
		int idx = (i == 0 ? A.y : (i == 1 ? B.y : C.y));
		if (idx >= 0 && idx < (int)_verticesText.size())
			uvs[i] = _verticesText[idx];
		else {
			glm::vec3 n = (idx >= 0 && idx < (int)_verticesNormal.size()) ? _verticesNormal[idx] : normal;
			uvs[i] = generateDefaultUV(positions[i], n);
		}
	}

	glm::vec3 normals[3];
	for (int i = 0; i < 3; ++i) {
		int idx = (i == 0 ? A.z : (i == 1 ? B.z : C.z));
		if (idx >= 0 && idx < (int)_verticesNormal.size())
			normals[i] = _verticesNormal[idx];
		else
			normals[i] = normal;
	}

	for (int i = 0; i < 3; ++i) {
		// Positions
		_vertices.push_back(positions[i].x - _center.x);
		_vertices.push_back(positions[i].y - _center.y);
		_vertices.push_back(positions[i].z - _center.z);

		// Texture coords
		_vertices.push_back(uvs[i].x);
		_vertices.push_back(uvs[i].y);
		_vertices.push_back(this->id);

		// Normals
		_vertices.push_back(normals[i].x);
		_vertices.push_back(normals[i].y);
		_vertices.push_back(normals[i].z);
	}
}

vec2	scop::generateDefaultUV(cref(glm::vec3) pos, cref(glm::vec3) normal) {
	glm::vec3 absN = glm::abs(normal);
	vec2 uv;

	if (absN.x >= absN.y && absN.x >= absN.z)
		uv = vec2(pos.z, pos.y);
	else if (absN.y >= absN.x && absN.y >= absN.z)
		uv = vec2(pos.x, pos.z);
   else
		uv = vec2(pos.x, pos.y);

	uv = (uv - vec2(0.0f));
	return (uv);
}

void	scop::computeBoundingBox() {
	if (_verticesPos.empty()) {
		_center = glm::vec3(0.0f);
		return;
	}

	float minX = _verticesPos[0].x, maxX = _verticesPos[0].x;
	float minY = _verticesPos[0].y, maxY = _verticesPos[0].y;
	float minZ = _verticesPos[0].z, maxZ = _verticesPos[0].z;

	for (size_t i = 0; i < _verticesPos.size(); ++i) {
		const glm::vec3 &v = _verticesPos[i];
		if (v.x < minX) minX = v.x;
		if (v.x > maxX) maxX = v.x;
		if (v.y < minY) minY = v.y;
		if (v.y > maxY) maxY = v.y;
		if (v.z < minZ) minZ = v.z;
		if (v.z > maxZ) maxZ = v.z;
	}

	_center = glm::vec3(
		(minX + maxX) / 2.0f,
		(minY + maxY) / 2.0f,
		(minZ + maxZ) / 2.0f
	);
}

str	scop::getMaterialFilename() {
	return (this->_materialFilename);
}

str	scop::getName() {
	return (this->_name);
}

std::vector<GLfloat>	scop::getVertices() {
	return (this->_vertices);
}

std::vector<GLuint>	scop::getIndices() {
	return (this->_indices);
}

int			scop::getSmooth() {
	return (this->_smooth);
}

glm::vec3	scop::getCenter() {
	return (this->_center);
}

GLuint	scop::getArrayId() {
	return (this->_arrayId);
}
