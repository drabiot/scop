/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:40 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/19 17:30:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"

int		WD_WIDTH = 800;
int		WD_HEIGHT = 800;
bool	DISPLAY = false;
bool	PAUSE = false;

float skyboxVertices[] = {
    // Positions (X, Y, Z)
    // Right face
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,

    // Left face
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,

    // Top face
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,

    // Bottom face
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,

    // Back face
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    // Front face
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f
};

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
		Shader	shaderSkybox("./src/shaders/skybox.vert", "./src/shaders/skybox.frag");
		utils	utils(data.getVertices());
		Camera	camera(glm::vec3(0.0f, 0.0f, 25.0f));

		//Skybox Shader
		shaderSkybox.Activate();
		glUniform1i(glGetUniformLocation(shaderSkybox.ID, "skybox"), 0);

		glEnable(GL_DEPTH_TEST);

		float 		rotation = 0.0f;
		float		lastFrame = 0.0f;
		const float	targetFPS = 60.0f;
		const float	targetFrameTime = 1.0f / targetFPS;
		float		mixFactor = 0.0f;
		float		transitionSpeed = 1.0f;

		//Create Skybox
		unsigned int skyboxVAO, skyboxVBO;
		glGenVertexArrays(1, &skyboxVAO);
		glGenBuffers(1, &skyboxVBO);

		glBindVertexArray(skyboxVAO);

		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

		// Attribut de vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


		str facesCubemap[6] =
		{
			"./resources/skybox/right.bmp",
			"./resources/skybox/left.bmp",
			"./resources/skybox/top.bmp",
			"./resources/skybox/bottom.bmp",
			"./resources/skybox/back.bmp",
			"./resources/skybox/front.bmp"
		};

		unsigned int	cubemapTexture;
		
		glGenTextures(1, &cubemapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// These are very important to prevent seams
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
		}

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

			// Clean the back buffer and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//DRAW SKYBOX
			glDepthFunc(GL_LEQUAL);
			shaderSkybox.Activate();

			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
			// The last row and column affect the translation of the skybox (which we don't want to affect)
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



			loopGame(data, window, shaderProgram, shaderSkybox, utils);
		}
		deleteUtils(window, shaderProgram, utils);
	} catch (const std::exception &e) {
		ERROR RED "Error: " AND e.what() CENDL;
	}
	return (0);
}