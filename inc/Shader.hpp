/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:31:48 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 15:06:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP

# include "utils.hpp"

str get_file_contents(const char *filename);

class Shader {
	public:
		GLuint	ID;
		Shader(const char *vertexFile, const char *fragmentFile);

		void	Activate(void);
		void	Delete(void);
};

#endif //SHADER_HPP
