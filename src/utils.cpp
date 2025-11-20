/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:26:14 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/20 19:18:29 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

void    opengErrorMsg(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	(void)length;
	(void)source;
	(void)id;
	(void)userParam;
	std::string severityColor;
	switch (severity){
		case GL_DEBUG_SEVERITY_LOW:
			severityColor = GREEN;
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			severityColor =  YELLOW;
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			severityColor =  RED;
			break;
		default:
			return ; //these are notifications and not really important
			severityColor =  WHITE;
	}

	PRINT RED "Opengl Message: " << severityColor;

	switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			PRINT "ERROR; ";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			PRINT "DEPRECATED_BEHAVIOR; ";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			PRINT "UNDEFINED_BEHAVIOR; ";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			PRINT "PORTABILITY; ";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			PRINT "PERFORMANCE; ";
			break;
		case GL_DEBUG_TYPE_OTHER:
			PRINT "OTHER; ";
			break;
		default:
			PRINT "NO TYPE; ";
	}

	PRINT message CENDL;
}

utils::utils(std::vector<GLfloat> vertices) : VBO1(vertices.data(), vertices.size() * sizeof(GLfloat)) {
	// Links VBO to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void *)0);
	//Color & Texture
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 9 * sizeof(float), (void *)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 9 * sizeof(float), (void *)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	//EBO1.Unbind();
}


void	initWindow(GLFWwindow **window) {
	//Initialize GLFW
	glfwInit();
	
	//Tell GLFW that we use version 3.3 of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		
	//Tell GLFW that we are using CORE profile so we only have modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Create a GLFW window object & protect it
	*window = glfwCreateWindow(WD_WIDTH, WD_HEIGHT, (str(WD_NAME) + ":").c_str(), NULL, NULL);
	
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
	glDebugMessageCallback(opengErrorMsg, 0);
}

void	createSkybox(Shader shaderSkybox, unsigned int *skyboxVAO, unsigned int *skyboxVBO, unsigned int *cubemapTexture) {
	shaderSkybox.Activate();
	glUniform1i(glGetUniformLocation(shaderSkybox.ID, "skybox"), 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	//Create Skybox
	glGenVertexArrays(1, skyboxVAO);
	glGenBuffers(1, skyboxVBO);

	glBindVertexArray(*skyboxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, *skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	// Attribut de vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenTextures(1, cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, *cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		Texture face(facesCubemap[i].c_str());
		if (face.data.empty()) {
		ERROR RED AND "Failed to load cubemap texture: " << facesCubemap[i] CENDL;
		}

		glTexImage2D(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
		0,
		GL_RGBA,
		face.width,
		face.height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		face.data.data()
		);
		face.Delete();
	}
}

void	drawSkybox(Shader shaderSkybox, Camera camera, unsigned int skyboxVAO, unsigned int cubemapTexture) {
	shaderSkybox.Activate();
	glDepthFunc(GL_LEQUAL);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
	projection = glm::perspective(glm::radians(45.0f), (float)WD_WIDTH / WD_HEIGHT, 0.1f, 100.0f);
	
	glUniformMatrix4fv(glGetUniformLocation(shaderSkybox.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderSkybox.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
		
	glDepthFunc(GL_LESS);
}

void	loopGame(scop data, GLFWwindow *window, Shader shaderProgram, Shader shaderSkybox, Camera camera, utils utils, unsigned int skyboxVAO, unsigned int cubemapTexture) {	
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawSkybox(shaderSkybox, camera, skyboxVAO, cubemapTexture);
			
	shaderProgram.Activate();

	// Tell OpenGL which Shader Program we want to use
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D_ARRAY, data.getArrayId());
	glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex"), 0);

	utils.VAO1.Bind();
	glDrawArrays(GL_TRIANGLES, 0, data.getVertices().size());

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void	deleteUtils(GLFWwindow *window, Shader shaderProgram, utils utils) {
	// Delete all the objects we've created
	utils.VAO1.Delete();
	utils.VBO1.Delete();

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
