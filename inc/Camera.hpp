/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:59:38 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/13 13:48:53 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "Shader.hpp"
# include "utils.hpp"

class Camera {
	public:
		glm::vec3	Position;
		glm::vec3	Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3	Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4	cameraMatrix = glm::mat4(1.0f);

		// Prevents the camera from jumping around when first clicking left click
		bool		firstClick = true;

		float		speed = 0.1f;
		float		sensi = 100.0f;

		Camera(glm::vec3 position);

		void		updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void		Matrix(Shader &shader, const char *uniform);
		void		Inputs(GLFWwindow *window);

		//Color
		glm::vec4	lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec3	lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
};

#endif //CAMERA_HPP
