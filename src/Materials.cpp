/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Materials.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:51:30 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/06 20:46:10 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

Material::Material() : name(""), ambientColor(0.0f, 0.0f, 0.0f), diffuseColor(0.0f, 0.0f, 0.0f), specularColor(0.0f, 0.0f, 0.0f), dissolve(1.0), illum(0), specularExponant(0.0), texture("") {};

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

void scop::parseMtl(str fileDir) {
    if (isDirectory(fileDir.c_str()))
        throw std::runtime_error("Can't open a directory as a file");

    std::ifstream file(fileDir);
    if (!file.is_open())
        throw std::runtime_error("Can't open file");

    Material current;
    str line;

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

        if (type == "newmtl") {
            if (!current.name.empty())
                _usemtl.push_back(current);
            current = Material();
            current.name = data;
        } else if (type == "Ka") {
            float r, g, b;
            std::istringstream(data) >> r >> g >> b;
            current.ambientColor = glm::vec3(r, g, b);
        } else if (type == "Kd") {
            float r, g, b;
            std::istringstream(data) >> r >> g >> b;
            current.diffuseColor = glm::vec3(r, g, b);
        } else if (type == "Ks") {
            float r, g, b;
            std::istringstream(data) >> r >> g >> b;
            current.specularColor = glm::vec3(r, g, b);
        } else if (type == "Ns") {
            double ns;
            std::istringstream(data) >> ns;
            current.specularExponant = ns;
        } else if (type == "d") {
            double d;
            std::istringstream(data) >> d;
            current.dissolve = d;
        } else if (type == "illum") {
            int illum;
            std::istringstream(data) >> illum;
            current.illum = illum;
        } else if (type == "map_Kd") {
            data.erase(std::remove_if(data.begin(), data.end(), [](unsigned char c){ return c == '\r' || c == '\t'; }), data.end());
            current.texture = data;
        }
    }
    if (!current.name.empty())
        _usemtl.push_back(current);

    file.close();
}

