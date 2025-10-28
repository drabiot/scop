/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:26:14 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/28 17:25:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

utils::utils(std::vector<GLfloat> vertices, std::vector<GLuint> indices) : VBO1(vertices.data(), vertices.size() * sizeof(GLfloat)), EBO1(indices.data(), indices.size() * sizeof(GLuint)) {
	// Generates Vertex Buffer Object and links it to vertices
	//VBO1 = VBO(vertices.data(), vertices.size() * sizeof(GLfloat));
	// Generates Element Buffer Object and links it to indices
	//EBO1 = EBO(indices.data(),  indices.size()  * sizeof(GLuint));

	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
	//Color & Texture
	/*VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));*/
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
}

void	initWindow(scop data, GLFWwindow **window) {
	//Initialize GLFW
	glfwInit();

	//Tell GLFW that we use version 3.3 of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	//Tell GLFW that we are using CORE profile so we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a GLFW window object & protect it
	*window = glfwCreateWindow(WD_WIDTH, WD_HEIGHT, (str(WD_NAME) + ":" + data.getName()).c_str(), NULL, NULL);

	if (!*window) {
		glfwTerminate();
		throw std::runtime_error(std::string("Failed to create GLFW window"));
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(*window);
}

void	initGlad() {
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, WD_WIDTH, WD_HEIGHT);
}

void	loopGame(scop data, GLFWwindow *window, Shader shaderProgram, Texture tx, utils utils) {
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Tell OpenGL which Shader Program we want to use
	shaderProgram.Activate();

	glfwGetWindowSize(window, &WD_WIDTH, &WD_HEIGHT);
	glViewport(0, 0, WD_WIDTH, WD_HEIGHT);

	tx.Bind(shaderProgram, 0);

	utils.VAO1.Bind();
	glDrawElements(GL_TRIANGLES, data.getIndices().size(), GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}