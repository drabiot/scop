/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Materials.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:51:30 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/19 21:25:22 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

Material::Material() : name(""), ambientColor(0.0f, 0.0f, 0.0f), diffuseColor(0.0f, 0.0f, 0.0f), specularColor(0.0f, 0.0f, 0.0f), dissolve(1.0), illum(0), specularExponant(0.0) {};

Material::~Material() {}

void scop::parseMtl(str fileDir, str fileSuffix) {
	int	id = 0;
    if (isDirectory(fileDir.c_str()))
        throw std::runtime_error("Can't open a directory as a file");

    std::ifstream file(fileDir);
    if (!file.is_open())
        throw std::runtime_error("Can't open file");

    Material	current;
    str			line;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        if (line.empty() || line[0] == '#')
            continue;

        std::istringstream iss(line);
        str	type;
        iss >> type;
        str	data;
        std::getline(iss, data);
        data.erase(0, data.find_first_not_of(" \t"));

        if (type == "newmtl") {
            if (!current.name.empty())
                _usemtl.insert({current.name, current});
			current = Material();
			current.texture.LoadImage("./resources/img/mylittleponey.bmp");
            current.name = data;
			current.id = id;
			id++;
        } else if (type == "Ka") {
            float r, g, b;
            std::istringstream(data) >> r >> g >> b;
            current.ambientColor = vec3(r, g, b);
        } else if (type == "Kd") {
            float r, g, b;
            std::istringstream(data) >> r >> g >> b;
            current.diffuseColor = vec3(r, g, b);
        } else if (type == "Ks") {
            float r, g, b;
            std::istringstream(data) >> r >> g >> b;
            current.specularColor = vec3(r, g, b);
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
            current.texture.LoadImage(str("./" + fileSuffix + data).c_str());
        }
    }
    if (!current.name.empty()) {
        _usemtl.insert({current.name, current});
	}

    file.close();
}

void	scop::makeTexArray() {
	int	layer = 0;
	int	height = 0;
	int	width = 0;
	int	depth = 0;

	for (auto mtl : this->_usemtl) {
		++layer;
		width = max(width, mtl.second.texture.width);
		height = max(height, mtl.second.texture.height);
	}


	glGenTextures(1, &_arrayId);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _arrayId);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, layer);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	for (auto mtl : this->_usemtl) {
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0,  mtl.second.id, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, mtl.second.texture.data.data());
		++depth;
	}

	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
