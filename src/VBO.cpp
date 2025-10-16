/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:51:51 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 15:09:10 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VBO.hpp"

VBO::VBO(GLfloat *vertices, GLsizeiptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void	VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void	VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void	VBO::Delete() {
	glDeleteBuffers(1, &ID);
}
