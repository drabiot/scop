/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VBO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:49:33 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 15:06:00 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VBO_HPP
# define VBO_HPP

# include "utils.hpp"

class VBO {
	public:
		GLuint	ID;
		VBO(GLfloat *vertices, GLsizeiptr size);

		void	Bind(void);
		void	Unbind(void);
		void	Delete(void);
};

#endif //VBO_HPP
