/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:02:27 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/17 17:03:52 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

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

scop::scop(char *filename) {
	std::ifstream	file(filename);
	str				line;

	if (file.is_open()) {
		while(std::getline(file, line)) {
			//look first word
			str	type = firstWord(line);
			str	data = lastWord(line);
			//PRINT BLUE AND type CENDL;
			//PRINT CYAN AND data CENDL;
			if (type == "o") {
				setName(data);
			}
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


str	scop::getMaterialFilename() {
	return (this->_materialFilename);
}

str	scop::getName() {
	return (this->_name);
}

const int	*scop::getVertices() {
	return (this->_vertices);
}

const int	*scop::getIndices() {
	return (this->_indices);
}

str	scop::getUsemtl() {
	return (this->_usemtl);
}

int			scop::getSmooth() {
	return (this->_smooth);
}
