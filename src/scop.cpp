/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:02:27 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/05 15:31:14 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

bool					isDirectory(const char *path);
str					firstWord(str content);
str					lastWord(str content);
std::vector<str>	split(str s, str delimiter);
bool					isCorrectDigit(str value);
str					trim(cref(str) s);


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

	str line;
	while (std::getline(file, line)) {
		str type = firstWord(line);
		str data = lastWord(line);

		if (type == "mtllib")
			setMaterialFilename(data);
		else if (type == "o")
			setName(data);
		else if (type == "usemtl")
			setUsemtl(data);
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
	}
	file.close();
}

scop::~scop() {}

void	scop::setMaterialFilename(str newMaterialFilename) {
	this->_materialFilename = newMaterialFilename;
}

void	scop::setName(str newName) {
	this->_name = newName;
}

void	scop::setUsemtl(str newUsemtl) {
	this->_usemtl = newUsemtl;
}

void	scop::setSmooth(int newSmooth) {
	this->_smooth = newSmooth;
}


void	scop::addVerticesPos(str newVertices) {
	std::vector<str>	values = split(newVertices, " ");
	GLfloat				v1, v2, v3;
	
	if (values.size() != 3)
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
	
	if (values.size() != 3)
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
	
	if (values.size() != 2)
		throw std::runtime_error(str("Not the right number of Vertices for Texture"));

	v1 = static_cast<GLfloat>(std::stod(values[0].c_str()));
	v2 = static_cast<GLfloat>(std::stod(values[1].c_str()));

	glm::vec2	pos(v1, v2);

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
		throw std::runtime_error(str("Not the right number of Indices"));
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

	glm::vec2 uvs[3];
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

		// Normals
		_vertices.push_back(normals[i].x);
		_vertices.push_back(normals[i].y);
		_vertices.push_back(normals[i].z);
	}
}

glm::vec2	scop::generateDefaultUV(cref(glm::vec3) pos, cref(glm::vec3) normal) {
	glm::vec3 absN = glm::abs(normal);
	glm::vec2 uv;

	if (absN.x >= absN.y && absN.x >= absN.z)
		uv = glm::vec2(pos.z, pos.y);
	else if (absN.y >= absN.x && absN.y >= absN.z)
		uv = glm::vec2(pos.x, pos.z);
   else
		uv = glm::vec2(pos.x, pos.y);

	uv = (uv - glm::vec2(0.0f));
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

str	scop::getUsemtl() {
	return (this->_usemtl);
}

int			scop::getSmooth() {
	return (this->_smooth);
}

glm::vec3	scop::getCenter() {
	return (this->_center);
}

//Utils

bool	isDirectory(const char *path) {
	struct stat s;
	if (stat(path, &s) == 0)
		return S_ISDIR(s.st_mode);
	return false;
}

str	firstWord(str content) {
	size_t	endWord = content.find(" ");
	str		firstWord = content.substr(0, endWord);
	
	return (firstWord);
}

str	lastWord(str content) {
	size_t	startPos = content.find(" ");
	str		lastWord = content.substr(startPos + 1, content.npos);
	
	return (lastWord);
}

std::vector<str>	split(str s, str delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	str token;
	std::vector<str> res;
	
	while ((pos_end = s.find(delimiter, pos_start)) != str::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}
	
	res.push_back (s.substr (pos_start));
	return res;
}

bool isCorrectDigit(str value) {
	if (value.empty())
		return (false);

	size_t	start = 0;

	if (value[0] == '-' || value[0] == '+') {
		if (value.size() == 1)
			return (false);
		start = 1;
	}

	for (size_t i = start; i < value.size(); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(value[i])))
			return (false);
	}
	return (true);
}

str trim(cref(str) s) {
	size_t start = s.find_first_not_of(" \t\r\n");
	
	if (start == str::npos)
		return ("");
	
	size_t end = s.find_last_not_of(" \t\r\n");
	return (s.substr(start, end - start + 1));
}
