/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:59:38 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/29 14:54:44 by tchartie         ###   ########.fr       */
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

		// Prevents the camera from jumping around when first clicking left click
		bool firstClick = true;

		float	speed = 0.1f;
		float sensi = 100.0f;

		Camera(glm::vec3 position);

		void	Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform);
		void	Inputs(GLFWwindow *window);
};

#endif //CAMERA_HPP
