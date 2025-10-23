/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:02:27 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/23 20:46:17 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

str					firstWord(str content);
str					lastWord(str content);
std::vector<str>	split(str string);
bool					isCorrectVertice(str vertice);
bool					isCorrectDigit(str value);

scop::scop(char *filename) {
	std::ifstream	file(filename);
	str				line;

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
				AddVertices(data);
			else if (type == "f")
				AddIndices(data);
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


void	scop::AddVertices(str newVertices) {
	std::vector<str>	values = split(newVertices);
	GLfloat				v1, v2, v3;

	if (values.size() != 3)
		throw std::runtime_error(std::string("Not the right number of Vertices"));

	if (!isCorrectVertice(values[0]) || !isCorrectVertice(values[1]) || !isCorrectVertice(values[2]))
		throw std::runtime_error(std::string("Invalid Vertice"));

	v1 = static_cast<GLfloat>(std::atof(values[0].c_str()));
	v2 = static_cast<GLfloat>(std::atof(values[1].c_str()));
	v3 = static_cast<GLfloat>(std::atof(values[2].c_str()));

	this->_vertices.push_back(v1);
	this->_vertices.push_back(v2);
	this->_vertices.push_back(v3);
}

void	scop::AddIndices(str newIndices) {
	std::vector<str>	values = split(newIndices);
	GLuint				v1, v2, v3, v4;

	if (values.size() == 3) {
		if (!isCorrectDigit(values[0]) || !isCorrectDigit(values[1]) || !isCorrectDigit(values[2]))
			throw std::runtime_error(std::string("Not the right number of Indices"));

		v1 = std::atoi(values[0].c_str());
		v2 = std::atoi(values[1].c_str());
		v3 = std::atoi(values[2].c_str());

		this->_indices.push_back(v1);
		this->_indices.push_back(v2);
		this->_indices.push_back(v3);
	}
	else if (values.size() == 4) {
		if (!isCorrectDigit(values[0]) || !isCorrectDigit(values[1]) || !isCorrectDigit(values[2]) || !isCorrectDigit(values[3]))
			throw std::runtime_error(std::string("Not the right number of Indices"));

		v1 = std::atoi(values[0].c_str());
		v2 = std::atoi(values[1].c_str());
		v3 = std::atoi(values[2].c_str());
		v4 = std::atoi(values[3].c_str());

		this->_indices.push_back(v1);
		this->_indices.push_back(v2);
		this->_indices.push_back(v3);

		this->_indices.push_back(v1);
		this->_indices.push_back(v4);
		this->_indices.push_back(v3);
	}
	else
		throw std::runtime_error(std::string("Not the right number of Indices"));
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

std::vector<str> split(str string) {
	std::vector<str>		tokens;
	std::istringstream	iss(string);
	str						token;
 
	while (iss >> token) {
		tokens.push_back(token);
	}

   return tokens;
}

bool	isCorrectVertice(str vertice) {
	(void)vertice;
	return (true);
}

bool isCorrectDigit(str value) {
    for (str::const_iterator it = value.begin(); it != value.end(); ++it) {
        if (!std::isdigit(static_cast<unsigned char>(*it))) {
            return (false);
        }
    }
    return (true);
}

