/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:37:49 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/21 16:15:38 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <vector>
# include <map>
# include <cctype>
# include <sys/stat.h>
# include <thread>
# include <chrono>
# include <sstream>
# include <algorithm> 

# include "glad.h"
# include "glfw3.h"

# include "color.hpp"

//TO DELETE
# define GLM_ENABLE_EXPERIMENTAL
# include "gtc/matrix_transform.hpp"
# include "gtc/type_ptr.hpp"
# include "glm.hpp"
# include "gtc/type_ptr.hpp"
# include "gtx/rotate_vector.hpp"
# include "gtx/vector_angle.hpp"

# define AND	<<
# define PRINT	std::cout AND
# define ERROR	std::cerr AND
# define NLINE	PRINT std::endl
# define ENDL	AND std::endl
# define CENDL	AND BASE_COLOR ENDL
# define TAB	"\t"

typedef std::string str;

# define cref(type) const type &
# define ref(type) type &

extern int	WD_WIDTH;
extern int	WD_HEIGHT;

extern bool	DISPLAY;
extern bool	PAUSE;

float				ease(float t);
bool				isDirectory(const char *path);
str					firstWord(str content);
str					lastWord(str content);
std::vector<str>	split(str s, str delimiter);
bool				isCorrectDigit(str value);
str					trim(cref(str) s);

static const float skyboxVertices[] = {
    // Right face
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,

    // Left face
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,

    // Top face
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,

    // Bottom face
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,

    // Back face
    -1.0f, 1.0f,  -1.0f,
     1.0f, 1.0f,  -1.0f,
     1.0f, 1.0f,   1.0f,
     1.0f, 1.0f,   1.0f,
    -1.0f, 1.0f,   1.0f,
    -1.0f, 1.0f,  -1.0f,

    // Front face
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f
};

static const str facesCubemap[6] = {
	"./resources/skybox/right.bmp",
	"./resources/skybox/left.bmp",
	"./resources/skybox/top.bmp",
	"./resources/skybox/bottom.bmp",
	"./resources/skybox/back.bmp",
	"./resources/skybox/front.bmp"
};

static GLfloat lightVertices[] = {
    // Triangle 0,1,2
    -0.1f,  0.1f, -0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,

    // Triangle 0,2,3
    -0.1f,  0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,

    // Triangle 0,4,7
    -0.1f,  0.1f, -0.1f,
    -0.1f,  0.1f,  0.1f,
     0.1f,  0.1f,  0.1f,

    // Triangle 0,7,3
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f,
     0.1f,  0.1f, -0.1f,

    // Triangle 3,7,6
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f,
     0.1f, -0.1f,  0.1f,

    // Triangle 3,6,2
     0.1f,  0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
     0.1f, -0.1f, -0.1f,

    // Triangle 2,6,5
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f,  0.1f,

    // Triangle 2,5,1
     0.1f, -0.1f, -0.1f,
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,

    // Triangle 1,5,4
    -0.1f, -0.1f, -0.1f,
    -0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,

    // Triangle 1,4,0
    -0.1f, -0.1f, -0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,

    // Triangle 4,5,6
    -0.1f,  0.1f,  0.1f,
    -0.1f, -0.1f,  0.1f,
     0.1f, -0.1f,  0.1f,

    // Triangle 4,6,7
    -0.1f,  0.1f,  0.1f,
     0.1f, -0.1f,  0.1f,
     0.1f,  0.1f,  0.1f
};



#endif //UTILS_HPP
