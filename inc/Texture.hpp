/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:10:34 by mbirou            #+#    #+#             */
/*   Updated: 2025/10/17 14:32:21 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Shader.hpp"

# define BMP_ID		0x4D42
# define HEADER_SIZE	26
# define MAX_SIZE		0x5F5E11A

class Texture
{
	public:
		GLuint	ID;
		GLenum	type;
		Texture(const char *path);

		void	LoadImage(const char *path);
		void	Bind(Shader &shader, int offset);
		void	Unbind();
		void	Delete();

		int								width;
		int								height;
		std::vector<unsigned char>	data;
};