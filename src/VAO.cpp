/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:58:58 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 15:10:04 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VAO.hpp"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void	VAO::LinkVBO(VBO VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
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
