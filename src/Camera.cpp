/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:06:19 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/15 18:31:42 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(vec3 position) {
	this->Position = position;
}

void	Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	mat4	view = mat4(1.0f);
	mat4	projection = mat4(1.0f);

	view = lookAt(Position, Position + Orientation, Up);
	projection = perspective(radians(FOVdeg), static_cast<float>(WD_WIDTH) / static_cast<float>(WD_HEIGHT), nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void	Camera::Matrix(Shader &shader, const char *uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, value_ptr(cameraMatrix));
}

void	Camera::Inputs(GLFWwindow *window) {
	// Handles Display inputs
	static bool	displayKey = false;
	static bool	pauseKey = false;
	static bool	greyKey = false;

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && !displayKey) {
		DISPLAY = !DISPLAY;
		displayKey = true;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE && displayKey)
		displayKey = false;

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !pauseKey) {
		PAUSE = !PAUSE;
		pauseKey = true;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && pauseKey)
		pauseKey = false;

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && !greyKey) {
		GREYKEY = !GREYKEY;
		greyKey = true;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE && greyKey)
		greyKey = false;


	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * Orientation;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position += speed * -normalize(cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position += speed * -Orientation;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Position += speed * normalize(cross(Orientation, Up));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Position += speed * Up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		Position += speed * -Up;
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		speed = 0.4f;
	else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
		speed = 0.1f;

	//Handle Light Color
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && lightColor.x < 1)
		this->lightColor.x += 0.00390625;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && lightColor.y < 1)
		this->lightColor.y += 0.00390625;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && lightColor.z < 1)
		this->lightColor.z += 0.00390625;

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && lightColor.x > 0)
		this->lightColor.x -= 0.00390625;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && lightColor.y > 0)
		this->lightColor.y -= 0.00390625;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && lightColor.z > 0)
		this->lightColor.z -= 0.00390625;


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (WD_WIDTH / 2), (WD_HEIGHT / 2));
			firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensi * (float)(mouseY - (WD_HEIGHT / 2)) / WD_HEIGHT;
		float rotY = sensi * (float)(mouseX - (WD_WIDTH / 2)) / WD_WIDTH;

		// Calculates upcoming vertical change in the Orientation
		vec3 newOrientation = rotate(Orientation, radians(-rotX), normalize(cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(angle(newOrientation, Up) - radians(90.0f)) <= radians(85.0f))
			Orientation = newOrientation;

		// Rotates the Orientation left and right
		Orientation = rotate(Orientation, radians(-rotY), Up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (WD_WIDTH / 2), (WD_HEIGHT / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}
