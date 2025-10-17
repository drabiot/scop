/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:40 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/17 16:55:16 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	0.5f, 1.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};


int main (int argc, char **argv)
{
	if (argc != 2) {
		ERROR RED ".obj file needed" CENDL;
		return (1);
	}
	try {

		scop data(argv[1]);


		//Initialize GLFW
		glfwInit();

		//Tell GLFW that we use version 3.3 of OpenGL
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		
		//Tell GLFW that we are using CORE profile so we only have modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Create a GLFW window object & protect it
		GLFWwindow *window = glfwCreateWindow(WD_WIDTH, WD_HEIGHT, (str(WD_NAME) + ":" + data.getName()).c_str(), NULL, NULL);
		if (!window) {
			ERROR RED "Failed to create GLFW window" CENDL;
			glfwTerminate();
			return (1);
		}

		// Introduce the window into the current context
		glfwMakeContextCurrent(window);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
		glViewport(0, 0, WD_WIDTH, WD_HEIGHT);
		
		// Generates Shader object using shaders defualt.vert and default.frag
		Shader shaderProgram("./src/shaders/default.vert", "./src/shaders/default.frag");

		VAO VAO1;
		VAO1.Bind();

		// Generates Vertex Buffer Object and links it to vertices
		VBO VBO1(vertices, sizeof(vertices));
		// Generates Element Buffer Object and links it to indices
		EBO EBO1(indices, sizeof(indices));

		// Links VBO to VAO
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
		VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
		// Unbind all to prevent accidentally modifying them
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();
		
		//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

		Texture tx("./resources/img/brick.bmp");

		float		rotation = 0.0f;
		double	prevTime = glfwGetTime();

		glEnable(GL_DEPTH_TEST);

		//Main loop
		while(!glfwWindowShouldClose(window)) {
			// Clean the back buffer and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Tell OpenGL which Shader Program we want to use
			shaderProgram.Activate();

			double crntTime = glfwGetTime();
			if (crntTime - prevTime >= 1 / 60) {
				rotation += 0.5f;
				prevTime = crntTime;
			}

			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 proj = glm::mat4(1.0f);

			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
			proj = glm::perspective(glm::radians(45.0f), (float)WD_WIDTH / WD_HEIGHT, 0.1f, 100.0f);

			int	modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			int	viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			int	projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

			//glUniform1f(uniID, 0.5f);
			tx.Bind(shaderProgram, 0);

			VAO1.Bind();
			glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// Delete all the objects we've created
		VAO1.Delete();
		VBO1.Delete();
		EBO1.Delete();
		tx.Delete();
		shaderProgram.Delete();

		//Delete window to avoid leaks
		glfwDestroyWindow(window);
		glfwTerminate();
	} catch (const std::exception &e) {
		ERROR RED "Error: " AND e.what() CENDL;
	}
	return (0);
}