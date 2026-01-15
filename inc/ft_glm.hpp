/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glm.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:54:45 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/15 19:38:34 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLM_HPP
# define FT_GLM_HPP

# include <cmath>

class	mat3;
class	mat4;

class	vec2 {
	public:
		vec2();
		vec2(float value);
		vec2(float newX, float newY);
		~vec2();

		vec2 operator-(const vec2& other) const;

		float x, y;
};

class	vec3 {
	public:
		vec3();
		vec3(float value);
		vec3(float newX, float newY, float newZ);
		~vec3();

		float x, y, z;
};

class	vec4 {
	public:
		vec4();
		vec4(float value);
		vec4(float newX, float newY, float newZ, float newW);
		~vec4();

		float x, y, z, w;
};

class mat3 {
public:
	mat3();
	mat3(float diagonal);
	mat3(const vec3& col0, const vec3& col1, const vec3& col2);
	mat3(const mat4& m);
	~mat3();

	vec3 c0, c1, c2;
};

class mat4 {
public:
	mat4();
	mat4(float diagonal);
	mat4(const vec4& A, const vec4& B, const vec4& C, const vec4& D);
	mat4(const mat3& m);
	~mat4();

	vec4 c0, c1, c2, c3;
};

// VEC3 Operators
vec3	operator-(const vec3& v);
vec3	operator-(const vec3& a, const vec3& b);
vec3	operator+(const vec3& a, const vec3& b);
vec3	operator*(float s, const vec3& v);
vec3&	operator+=(vec3& a, const vec3& b);

// MAT3 Operators
vec3	operator*(const mat3& m, const vec3& v);
mat3	operator*(const mat3& a, const mat3& b);

// MAT4 Operators
vec4	operator*(const mat4& m, const vec4& v);
mat4	operator*(const mat4& a, const mat4& b);

// Math functions
float	radians(float deg);
float	abs(float v);
vec3	abs(const vec3& v);
float	max(float a, float b);
float	min(float a, float b);
vec3	normalize(const vec3& v);
vec3	cross(const vec3& a, const vec3& b);
float	dot(const vec3& a, const vec3& b);
float	angle(const vec3& a, const vec3& b);

// GLM-like functions
const float*	value_ptr(const mat4& m);
const float*	value_ptr(const vec3& v);

mat4	translate(const mat4& m, const vec3& v);
mat4	translate(const vec3& v);
vec3	rotate(const vec3& v, float angle, const vec3& axis);
mat4	rotate(float angle, const vec3& axis);
mat4	rotate(const mat4& m, float angle, const vec3& axis);
mat4	lookAt(const vec3& eye, const vec3& center, const vec3& up);
mat4	perspective(float fov, float aspect, float near, float far);
mat4	ortho(float l, float r, float b, float t, float n, float f);

#endif //FT_GLM_HPP
