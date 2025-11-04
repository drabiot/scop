/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:02:27 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/04 18:30:11 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

str					firstWord(str content);
str					lastWord(str content);
std::vector<str>	split(str s, str delimiter);
bool					isCorrectVertice(str vertice);
bool					isCorrectDigit(str value);
str					trim(cref(str) s);



scop::scop(char *filename) {
	//parsing
	std::ifstream	file(filename);
	str				line;
	
	if (!file.is_open())
		throw std::runtime_error(std::string("Can't open file"));
	if (file.is_open()) {
		while(std::getline(file, line)) {
			str	type = firstWord(line);
			str	data = lastWord(line);
			if (type == "mtllib")
				setMaterialFilename(data);
			else if (type == "o")
				setName(data);
			else if (type == "usemlt")
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
		throw std::runtime_error(std::string("Not the right number of Vertices for Position"));

	if (!isCorrectVertice(values[0]) || !isCorrectVertice(values[1]) || !isCorrectVertice(values[2]))
		throw std::runtime_error(std::string("Invalid Vertice"));

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
		throw std::runtime_error(std::string("Not the right number of Vertices for Normal"));

	if (!isCorrectVertice(values[0]) || !isCorrectVertice(values[1]) || !isCorrectVertice(values[2]))
		throw std::runtime_error(std::string("Invalid Vertice"));

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
		throw std::runtime_error(std::string("Not the right number of Vertices for Texture"));

	if (!isCorrectVertice(values[0]) || !isCorrectVertice(values[1]))
		throw std::runtime_error(std::string("Invalid Vertice"));

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
		throw std::runtime_error(std::string("Not the right number of Indices"));
}

glm::vec3	scop::parseIndices(str indice) {
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
		else
			uvs[i] = glm::vec2(0.0f, 0.0f); //Create Correct Textures
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
		_vertices.push_back(positions[i].x);
		_vertices.push_back(positions[i].y);
		_vertices.push_back(positions[i].z);

		// Texture coords
		_vertices.push_back(uvs[i].x);
		_vertices.push_back(uvs[i].y);

		// Normals
		_vertices.push_back(normals[i].x);
		_vertices.push_back(normals[i].y);
		_vertices.push_back(normals[i].z);
	}
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

//Utils

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
	std::string token;
	std::vector<std::string> res;
	
	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}
	
	res.push_back (s.substr (pos_start));
	return res;
}

bool	isCorrectVertice(str vertice) {
	(void)vertice;
	return (true);
}

bool isCorrectDigit(str value) {
	if (value.empty())
		return (false);

	size_t start = 0;

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
