/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:37:49 by tchartie          #+#    #+#             */
/*   Updated: 2025/11/19 17:08:36 by tchartie         ###   ########.fr       */
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

#endif //UTILS_HPP
