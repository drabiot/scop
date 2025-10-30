/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:02:27 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/30 16:31:05 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

str					firstWord(str content);
str					lastWord(str content);
std::vector<str>	split(str s, str delimiter);
bool					isCorrectVertice(str vertice);
bool					isCorrectDigit(str value);

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
				addVertices(data);
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


void	scop::addVertices(str newVertices) {
	std::vector<str>	values = split(newVertices, " ");
	GLfloat				v1, v2, v3;

	if (values.size() != 3)
		throw std::runtime_error(std::string("Not the right number of Vertices"));

	if (!isCorrectVertice(values[0]) || !isCorrectVertice(values[1]) || !isCorrectVertice(values[2]))
		throw std::runtime_error(std::string("Invalid Vertice"));

	v1 = static_cast<GLfloat>(std::stod(values[0].c_str()));
	v2 = static_cast<GLfloat>(std::stod(values[1].c_str()));
	v3 = static_cast<GLfloat>(std::stod(values[2].c_str()));

	glm::vec3	pos(v1, v2, v3);

	this->_verticesPos.push_back(pos);
	this->_verticesText.resize(this->_verticesPos.size());
}

void	scop::addIndices(str newIndices) {
	std::vector<str>	values = split(newIndices, " ");
	GLuint				v1, v2, v3, v4;

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

GLuint	scop::parseIndices(str indice) {
	if ((indice.find('/')) != str::npos) {
		std::vector<str>	values = split(indice, "/");

		if (!isCorrectDigit(values[0]) && !isCorrectDigit(values[1]) && !isCorrectDigit(values[2]))
			throw std::runtime_error(std::string("Indices isn't a number"));

		_indices.push_back(std::atoi(values[0].c_str()) - 1);
		_indicesText.push_back(std::atoi(values[1].c_str()) - 1);
		_indicesNormal.push_back(std::atoi(values[2].c_str()) - 1);

		return (std::atoi(values[0].c_str()) - 1);
	}
	else if (isCorrectDigit(indice)) {
		_indices.push_back(std::atoi(indice.c_str()) - 1);

		return (std::atoi(indice.c_str()) - 1);
	}
	else
		throw std::runtime_error(std::string("Not the right number of Indices"));
}

void scop::normalizeVector(int A, int B, int C) {
	glm::vec3 normal = glm::normalize(glm::cross(
		_verticesPos[B] - _verticesPos[A],
		_verticesPos[C] - _verticesPos[A]
	));

	glm::vec3 positions[3] = { _verticesPos[A], _verticesPos[B], _verticesPos[C] };

	for (int i = 0; i < 3; ++i) {
		_vertices.push_back(positions[i].x);
		_vertices.push_back(positions[i].y);
		_vertices.push_back(positions[i].z);

		_vertices.push_back(normal.x);
		_vertices.push_back(normal.y);
		_vertices.push_back(normal.z);
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

