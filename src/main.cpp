/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:40 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/19 14:03:42 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

int		WD_WIDTH = 800;
int		WD_HEIGHT = 800;
bool	DISPLAY = false;
bool	PAUSE = false;

int main (int argc, char **argv)
{
	if (argc != 2) {
		ERROR RED ".obj file needed" CENDL;
		return (1);
	}
	try {
		GLFWwindow *window;
		initWindow(&window);
		initGlad();
		scop data(argv[1]);
		

		Shader	shaderProgram("./src/shaders/default.vert", "./src/shaders/default.frag");
		utils	utils(data.getVertices());
		Camera	camera(glm::vec3(0.0f, 0.0f, 25.0f));

		glEnable(GL_DEPTH_TEST);

		float 		rotation = 0.0f;
		float		lastFrame = 0.0f;
		const float	targetFPS = 60.0f;
		const float	targetFrameTime = 1.0f / targetFPS;
		float		mixFactor = 0.0f;
		float		transitionSpeed = 1.0f;

		//Main Game loop
		while(!glfwWindowShouldClose(window)) {
			float	currentFrame = static_cast<float>(glfwGetTime());
			float	deltaTime = currentFrame - lastFrame;

			if (deltaTime < targetFrameTime) {
				float	waitTime = targetFrameTime - deltaTime;
				std::this_thread::sleep_for(std::chrono::duration<float>(waitTime));
				currentFrame = static_cast<float>(glfwGetTime());
				deltaTime = currentFrame - lastFrame;

			}
			lastFrame = currentFrame;

			std::string title = "scop:" + data.getName() + " FPS " + std::to_string(1.0f / deltaTime);
			glfwSetWindowTitle(window, title.c_str());
			if (!PAUSE)
				rotation += 1.0f * deltaTime;

			//Fade Display
			float target = DISPLAY ? 1.0f : 0.0f;
			
			mixFactor += (target - mixFactor) * transitionSpeed * deltaTime;

			if (mixFactor < 0.0f) mixFactor = 0.0f;
			if (mixFactor > 1.0f) mixFactor = 1.0f;

			float easedMix = ease(mixFactor);

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, rotation, glm::vec3(0.0f, 1.0f, 0.0f));

			shaderProgram.Activate();
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniform1f(glGetUniformLocation(shaderProgram.ID, "mixFactor"), easedMix);


			// Camera & Viewport
			camera.Inputs(window);
			camera.Matrix(45.0f, 0.1f, 1024.0f, shaderProgram, "camMatrix");
			glfwGetWindowSize(window, &WD_WIDTH, &WD_HEIGHT);
			glViewport(0, 0, WD_WIDTH, WD_HEIGHT);

			loopGame(data, window, shaderProgram, utils);
		}


		deleteUtils(window, shaderProgram, utils);
	} catch (const std::exception &e) {
		ERROR RED "Error: " AND e.what() CENDL;
	}
	return (0);
}