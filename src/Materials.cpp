/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Materials.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:51:30 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/06 20:14:29 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

Material::Material(str file, glm::vec3 amCo, glm::vec3 diCo, glm::vec3 spCo, double diss, int illum, double spExp, str tex) {
	this->name = file;
	this->ambientColor = amCo;
	this->diffuseColor = diCo;
	this->specularColor = spCo;
	this->dissolve = diss;
	this->illum = illum;
	this->specularExponant = spExp;
	this->texture = tex;
}

Material::~Material() {}


void	parseMtl(str fileDir) {
	if (isDirectory(fileDir.c_str()))
		throw std::runtime_error("Can't open a directory as a file");

	std::ifstream file(fileDir);
	if (!file.is_open())
		throw std::runtime_error("Can't open file");

	str line;
	while (std::getline(file, line)) {
		str	type = firstWord(line);
		str	data = lastWord(line);

		//bool	isNewMtl = true;

		(void)data;
		/*if (type == "newmtl") {

		}*/
	}
	file.close();
}
