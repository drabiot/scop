/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EBO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:55:22 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 15:06:10 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EBO_HPP
# define EBO_HPP

# include "utils.hpp"

class EBO {
	public:
		GLuint	ID;
		EBO(GLuint *indices, GLsizeiptr size);

		void	Bind(void);
		void	Unbind(void);
		void	Delete(void);
};

#endif //EBO_HPP
