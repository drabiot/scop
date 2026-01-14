/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glm.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:36:58 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/14 13:46:01 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glm.hpp"

vec2::vec2() {
	this->x = 0;
	this->y = 0;
}

vec2::vec2(float value) {
	this->x = value;
	this->y = value;
}

vec2::vec2(float newX, float newY) {
	this->x = newX;
	this->y = newY;
}

vec2::~vec2(void) {}

vec2 vec2::operator-(const vec2& other) const {
	return vec2(
		this->x - other.x,
		this->y - other.y
	);
}
