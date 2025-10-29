/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:40 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/29 19:58:41 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

int	WD_WIDTH = 800;
int	WD_HEIGHT = 800;

int main (int argc, char **argv)
{
	if (argc != 2) {
		ERROR RED ".obj file needed" CENDL;
		return (1);
	}
	try {
		scop data(argv[1]);

		GLFWwindow *window;
		initWindow(data, &window);
		initGlad();

		Shader	shaderProgram("./src/shaders/default.vert", "./src/shaders/default.frag");
		utils		utils(data.getVertices(), data.getIndices());
		Texture	tx("./resources/img/brick.bmp");
		Camera	camera(glm::vec3(0.0f, 0.0f, 25.0f));

		glEnable(GL_DEPTH_TEST);

		//Main Game loop
		while(!glfwWindowShouldClose(window)) {
			camera.Inputs(window);
			camera.Matrix(45.0f, 0.1f, 1024.0f, shaderProgram, "camMatrix");
			glfwGetWindowSize(window, &WD_WIDTH, &WD_HEIGHT);
			glViewport(0, 0, WD_WIDTH, WD_HEIGHT);
			loopGame(data, window, shaderProgram, tx, utils);
		}

		deleteUtils(window, shaderProgram, tx, utils);
	} catch (const std::exception &e) {
		ERROR RED "Error: " AND e.what() CENDL;
	}
	return (0);
}