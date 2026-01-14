/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glm.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:17:29 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/14 13:45:36 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLM_HPP
# define FT_GLM_HPP

class	vec2 {
	public:
		vec2();
		vec2(float value);
		vec2(float newX, float newY);
		~vec2(void);

		vec2 operator-(const vec2& other) const;

		float	x;
		float	y;
};

class	vec3 {
	public:
		vec3();
		vec3(float newX, float newY, float newZ);
		~vec3(void);

		float	x;
		float	y;
		float	z;
};

class	vec4 {
	public:
		vec4();
		vec4(float newX, float newY, float newZ, float newW);
		~vec4(void);

		float	x;
		float	y;
		float	z;
		float	w;
};

class	mat4 {

};

#endif //FT_GLM_HPP
