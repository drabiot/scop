/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:58:58 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/28 17:23:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VAO.hpp"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
	this->Bind();
}

void	VAO::LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void	VAO::Bind() {
	glBindVertexArray(ID);
}

void	VAO::Unbind() {
	glBindVertexArray(0);
}

void	VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}
