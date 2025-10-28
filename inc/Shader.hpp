/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:31:48 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/28 16:48:51 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP

# include "utils.hpp"

str get_file_contents(const char *filename);

class Shader {
	public:
		Shader(void);
		Shader(const char *vertexFile, const char *fragmentFile);
		
		void	Activate(void);
		void	Delete(void);
		
		GLuint	ID;
};

#endif //SHADER_HPP
