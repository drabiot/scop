/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:59:38 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/14 14:54:16 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "Shader.hpp"
# include "utils.hpp"

class Camera {
	public:
		vec3	Position;
		vec3	Orientation = vec3(0.0f, 0.0f, -1.0f);
		vec3	Up = vec3(0.0f, 1.0f, 0.0f);
		mat4	cameraMatrix = mat4(1.0f);

		// Prevents the camera from jumping around when first clicking left click
		bool	firstClick = true;

		float	speed = 0.1f;
		float	sensi = 100.0f;

		Camera(vec3 position);

		void	updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void	Matrix(Shader &shader, const char *uniform);
		void	Inputs(GLFWwindow *window);

		//Color
		vec4	lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		vec3	lightPos = vec3(0.5f, 0.5f, 0.5f);
};

#endif //CAMERA_HPP
