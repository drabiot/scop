/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VAO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:49:33 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 15:06:02 by tchartie         ###   ########.fr       */
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

		void	LinkVBO(VBO VBO, GLuint layout);
		void	Bind(void);
		void	Unbind(void);
		void	Delete(void);
};

#endif //VAO_HPP
