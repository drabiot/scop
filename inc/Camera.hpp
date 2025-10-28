/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:59:38 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/28 15:49:59 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# define GLM_ENABLE_EXPERIMENTAL
# include "glad/glad.h"
# include "GLFW/glfw3.h"
# include "glm.hpp"
# include "gtc/type_ptr.hpp"
# include "gtx/rotate_vector.hpp"
# include "gtx/vector_angle.hpp"

# include "Shader.hpp"

class Camera {
	public:
		glm::vec3	Position;
		glm::vec3	Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3	Up = glm::vec3(0.0f, 1.0f, 0.0f);

		// Prevents the camera from jumping around when first clicking left click
		bool firstClick = true;

		int	width;
		int	height;

		float	speed = 0.1f;
		float sensi = 100.0f;

		Camera(int width, int height, glm::vec3 position);

		void	Matrix(float FOVdeg, float nearPlane, float farPlane, Shader &shader, const char *uniform);
		void	Inputs(GLFWwindow *window);
};

#endif //CAMERA_HPP
