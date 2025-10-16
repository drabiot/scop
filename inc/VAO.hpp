/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:49:33 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 18:16:19 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAO_HPP
# define VAO_HPP

# include "utils.hpp"
# include "VBO.hpp"

class VAO {
	public:
		GLuint	ID;
		VAO(void);

		void	LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
		void	Bind(void);
		void	Unbind(void);
		void	Delete(void);
};

#endif //VAO_HPP
