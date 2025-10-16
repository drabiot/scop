/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:40 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/16 13:45:31 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

int main (int argc, char **argv)
{
	(void)argc;
	(void)argv;

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 800, "scop", NULL, NULL);
	if (!window) {
		PRINT RED "Failed to create GLFW window" CENDL;
		glfwTerminate();
		return (1);
	}

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwMakeContextCurrent(window);

	glfwTerminate();
	return (0);
}