/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:00:49 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/07 18:15:56 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_HPP
# define SCOP_HPP

# include "utils.hpp"
# include "Shader.hpp"
# include "VAO.hpp"
# include "VBO.hpp"
# include "EBO.hpp"
# include "Texture.hpp"
# include "Camera.hpp"
# include "Materials.hpp"

# define WD_NAME "scop"

class scop {
	public:
		scop(char *filename);
		~scop(void);

		void							setMaterialFilename(str newMaterialFilename, char *filename);
		void							setName(str newName);
		void							setUsemtl(str newUsemtl);
		void							setSmooth(int newSmooth);

		void							addVerticesPos(str newVertices);
		void							addVerticesNormal(str newVertices);
		void							addVerticesText(str newVertices);
		void							parseMtl(str fileDir, str fileSuffix);
		void							makeTexArray(void);
		void							addIndices(str newIndices);
		glm::vec3					parseIndices(str indice);
		void							normalizeVector(glm::vec3 A, glm::vec3 B, glm::vec3 C);
		glm::vec2					generateDefaultUV(cref(glm::vec3) pos, cref(glm::vec3) normal);
		void							computeBoundingBox(void);

		str							getMaterialFilename(void);
		str							getName(void);
		std::vector<GLfloat>		getVertices(void);
		std::vector<GLuint>		getIndices(void);
		std::vector<Material>	getUsemtl(void);
		int							getSmooth(void);
		glm::vec3					getCenter(void);
		
	private:
		str							_materialFilename;
		str							_name;
		std::vector<Material>	_usemtl;
		int							_smooth;
		std::vector<GLfloat>		_vertices;
		std::vector<GLuint>		_indices;

		glm::vec3					_center;
		bool							_centerDefine;
		
		std::vector<glm::vec3>	_verticesPos;
		std::vector<glm::vec3>	_verticesNormal;
		std::vector<glm::vec2>	_verticesText;

		std::vector<GLuint>		_indicesNormal;
		std::vector<GLuint>		_indicesText;

		GLuint						_arrayId = 0;
};

class	utils {
	public:
		utils(std::vector<GLfloat> vertices);

		VAO	VAO1;
		VBO	VBO1;
};

void	initWindow(GLFWwindow **window);
void	initGlad(void);
void	loopGame(scop data, GLFWwindow *window, Shader shaderProgram, Texture tx, utils utils);
void	deleteUtils(GLFWwindow *window, Shader shaderProgram, Texture tx, utils utils);

#endif //SCOP_HPP
