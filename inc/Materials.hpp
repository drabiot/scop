/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Materials.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:52:39 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/06 20:26:19 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_HPP
# define MATERIALS_HPP

# include "utils.hpp"

class Material {
	public:
		Material(void);
		Material(str file, glm::vec3 amCo, glm::vec3 diCo, glm::vec3 spCo, double diss, int illum, double spExp, str tex);
		~Material(void);

		str			name;
		glm::vec3	ambientColor;
		glm::vec3	diffuseColor;
		glm::vec3	specularColor;
		double		dissolve;				//Transparency
		int			illum;					//Type of illumination
		double		specularExponant;		//Shininess
		str			texture;
};

#endif //MATERIALS_HPP
