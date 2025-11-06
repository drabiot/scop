/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:26:14 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/06 20:22:42 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

utils::utils(std::vector<GLfloat> vertices) : VBO1(vertices.data(), vertices.size() * sizeof(GLfloat)) {
	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
	//Color & Texture
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void *)(5 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	//EBO1.Unbind();
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
	glViewport(0, 0, WD_WIDTH, WD_HEIGHT);
}

void	loopGame(scop data, GLFWwindow *window, Shader shaderProgram, Texture tx, utils utils) {
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Tell OpenGL which Shader Program we want to use
	shaderProgram.Activate();

	tx.Bind(shaderProgram, 0);

	utils.VAO1.Bind();
	glDrawArrays(GL_TRIANGLES, 0, data.getVertices().size());
	//glDrawElements(GL_TRIANGLES, data.getIndices().size(), GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void	deleteUtils(GLFWwindow *window, Shader shaderProgram, Texture tx, utils utils) {
	// Delete all the objects we've created
	utils.VAO1.Delete();
	utils.VBO1.Delete();
	//utils.EBO1.Delete();
	tx.Delete();
	shaderProgram.Delete();

	//Delete window to avoid leaks
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool	isDirectory(const char *path) {
	struct stat s;
	if (stat(path, &s) == 0)
		return S_ISDIR(s.st_mode);
	return false;
}

str	firstWord(str content) {
	size_t	endWord = content.find(" ");
	str		firstWord = content.substr(0, endWord);
	
	return (firstWord);
}

str	lastWord(str content) {
	size_t	startPos = content.find(" ");
	str		lastWord = content.substr(startPos + 1, content.npos);
	
	return (lastWord);
}

std::vector<str>	split(str s, str delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	str token;
	std::vector<str> res;
	
	while ((pos_end = s.find(delimiter, pos_start)) != str::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}
	
	res.push_back (s.substr (pos_start));
	return res;
}

bool isCorrectDigit(str value) {
	if (value.empty())
		return (false);

	size_t	start = 0;

	if (value[0] == '-' || value[0] == '+') {
		if (value.size() == 1)
			return (false);
		start = 1;
	}

	for (size_t i = start; i < value.size(); ++i) {
		if (!std::isdigit(static_cast<unsigned char>(value[i])))
			return (false);
	}
	return (true);
}

str trim(cref(str) s) {
	size_t start = s.find_first_not_of(" \t\r\n");
	
	if (start == str::npos)
		return ("");
	
	size_t end = s.find_last_not_of(" \t\r\n");
	return (s.substr(start, end - start + 1));
}

float	ease(float t) {
	return t * t * (3.0f - 2.0f * t);
}
