/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:49 by tchartie          #+#    #+#             */
/*   Updated: 2026/01/14 14:56:26 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_HPP
# define SCOP_HPP

# include "utils.hpp"
# include "Shader.hpp"
# include "VAO.hpp"
# include "VBO.hpp"
# include "Texture.hpp"
# include "Camera.hpp"
# include "Materials.hpp"

# define WD_NAME "scop"

class scop {
	public:
		scop(char *filename);
		~scop(void);

		void					setMaterialFilename(str newMaterialFilename, char *filename);
		void					setName(str newName);
		void					setUsemtl(str newUsemtl);
		void					setSmooth(int newSmooth);

		void					addVerticesPos(str newVertices);
		void					addVerticesNormal(str newVertices);
		void					addVerticesText(str newVertices);
		void					parseMtl(str fileDir, str fileSuffix);
		void					makeTexArray(void);
		void					addIndices(str newIndices);
		vec3					parseIndices(str indice);
		void					normalizeVector(vec3 A, vec3 B, vec3 C);
		vec2					generateDefaultUV(cref(vec3) pos, cref(vec3) normal);
		void					computeBoundingBox(void);

		str						getMaterialFilename(void);
		str						getName(void);
		std::vector<GLfloat>	getVertices(void);
		std::vector<GLuint>		getIndices(void);
		int						getSmooth(void);
		vec3					getCenter(void);
		GLuint					getArrayId(void);

		int						id = 0;
		
	private:
		str						_materialFilename;
		str						_name;
		std::map<str, Material>	_usemtl;
		int						_smooth;
		std::vector<GLfloat>	_vertices;
		std::vector<GLuint>		_indices;

		vec3					_center;
		bool					_centerDefine;
		
		std::vector<vec3>		_verticesPos;
		std::vector<vec3>		_verticesNormal;
		std::vector<vec2>		_verticesText;

		std::vector<GLuint>		_indicesNormal;
		std::vector<GLuint>		_indicesText;

		GLuint					_arrayId = 0;

};

class	utils {
	public:
		utils(std::vector<GLfloat> vertices);

		VAO	VAO1;
		VBO	VBO1;
};

void	initWindow(GLFWwindow **window);
void	initGlad(void);
void	createSkybox(Shader shaderSkybox, unsigned int *skyboxVAO, unsigned int *skyboxVBO, unsigned int *cubemapTexture);
void	loopGame(scop data, GLFWwindow *window, Shader shaderProgram, Shader shaderSkybox, Camera camera, utils utils, unsigned int skyboxVAO, unsigned int cubemapTexture);
void	deleteUtils(GLFWwindow *window, Shader shaderProgram, utils utils);

#endif //SCOP_HPP
