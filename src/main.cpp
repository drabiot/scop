/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:40 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/14 13:09:20 by tchartie         ###   ########.fr       */
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
		Shader	shaderSkybox("./src/shaders/skybox.vert", "./src/shaders/skybox.frag");
		Shader	shaderLight("./src/shaders/light.vert", "./src/shaders/light.frag");
		Shader	shaderShadow("./src/shaders/shadow.vert", "./src/shaders/shadow.frag");
		utils	utils(data.getVertices());
		Camera	camera(glm::vec3(0.0f, 0.0f, 25.0f));

		float 			rotation = 0.0f;
		float			mixFactor = 0.0f;
		float			transitionSpeed = 1.0f;
		double			prevTime = 0.0;
		double			crntTime = 0.0;
		double			deltaTime;
		unsigned  int	counter = 0;
		unsigned int	skyboxVAO, skyboxVBO;
		unsigned int	cubemapTexture;

		createSkybox(shaderSkybox, &skyboxVAO, &skyboxVBO, &cubemapTexture);

		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, camera.lightPos);


		shaderLight.Activate();
		shaderProgram.Activate();
		int li = glGetUniformLocation(shaderProgram.ID, "lightColor");
		glUniform4f(li, camera.lightColor.x, camera.lightColor.y, camera.lightColor.z, camera.lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), camera.lightPos.x, camera.lightPos.y, camera.lightPos.z);


		//Create FrameBuffer for the Shadow Map
		unsigned int	shadowMapFBO;
		glGenFramebuffers(1, &shadowMapFBO);

		unsigned int	shadowMapWidth = 2048, shadowMapHeight = 2048;
		unsigned int	shadowMap;
		glGenTextures(1, &shadowMap);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float	clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

		glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		glm::mat4	orthogonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
		glm::mat4	lightView = glm::lookAt(20.0f * camera.lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4	lightProjection = orthogonalProjection * lightView;


		
		
		//Main Game loop
		while(!glfwWindowShouldClose(window)) {
			// Clean the back buffer and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			
			crntTime = glfwGetTime();
			deltaTime = crntTime - prevTime;
			counter++;
			if (deltaTime >= 1.0 / 30.0) {
				str FPS	= std::to_string((1.0 / deltaTime) * counter);
				str	ms	= std::to_string((deltaTime / counter) * 1000);
				
				str	newTitle = "scop:" + data.getName() + " FPS:" + FPS + " ms:" + ms;
				glfwSetWindowTitle(window, newTitle.c_str());
				prevTime = crntTime;
				counter = 0;
			}
			
			if (!PAUSE)
			rotation += 1.0f * deltaTime;
		
			float	target = DISPLAY ? 1.0f : 0.0f;
			
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
			
			shaderShadow.Activate();
			glUniformMatrix4fv(glGetUniformLocation(shaderShadow.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));
			glUniformMatrix4fv(glGetUniformLocation(shaderShadow.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			
			//Shadows experimental
			glEnable(GL_DEPTH_TEST);

			glViewport(0, 0, shadowMapWidth, shadowMapHeight);
			glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
			glClear(GL_DEPTH_BUFFER_BIT);

			utils.VAO1.Bind();
			glDrawArrays(GL_TRIANGLES, 0, data.getVertices().size());

			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			//Fade Display
			mixFactor += (target - mixFactor) * transitionSpeed * deltaTime;
		
			if (mixFactor < 0.0f) mixFactor = 0.0f;
			if (mixFactor > 1.0f) mixFactor = 1.0f;
				
			float easedMix = ease(mixFactor);


			shaderProgram.Activate();
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniform1f(glGetUniformLocation(shaderProgram.ID, "mixFactor"), easedMix);
			

			// Camera & Viewport
			camera.Inputs(window);
			camera.updateMatrix(45.0f, 0.1f, 1024.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
			camera.Matrix(shaderProgram, "camMatrix");

			glfwGetWindowSize(window, &WD_WIDTH, &WD_HEIGHT);
			glViewport(0, 0, WD_WIDTH, WD_HEIGHT);

			shaderLight.Activate();
			camera.Matrix(shaderLight, "camMatrix");
			glDrawArrays(GL_TRIANGLES, 0, 36);
			shaderProgram.Activate();
			glUniform4f(li, camera.lightColor.x, camera.lightColor.y, camera.lightColor.z, camera.lightColor.w);

			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, shadowMap);
			glUniform1i(glGetUniformLocation(shaderProgram.ID, "uShadow"), 1);
			glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightPos"), 1, glm::value_ptr(camera.lightPos));
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));

			loopGame(data, window, shaderProgram, shaderSkybox, camera, utils, skyboxVAO, cubemapTexture);
		}
		deleteUtils(window, shaderProgram, utils);
	} catch (const std::exception &e) {
		ERROR RED "Error: " AND e.what() CENDL;
	}
	return (0);
}
