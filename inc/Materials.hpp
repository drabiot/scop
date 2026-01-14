/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Materials.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 19:52:39 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/14 14:56:12 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_HPP
# define MATERIALS_HPP

# include "utils.hpp"
# include "Texture.hpp"

class Material {
	public:
		Material(void);
		~Material(void);

		int		id;
		str		name;
		vec3	ambientColor;
		vec3	diffuseColor;
		vec3	specularColor;
		double	dissolve;				//Transparency
		int		illum;					//Type of illumination
		double	specularExponant;		//Shininess
		Texture	texture;
};

#endif //MATERIALS_HPP
