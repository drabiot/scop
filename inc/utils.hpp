/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:37:49 by tchartie          #+#    #+#             */
/*   Updated: 2025/10/29 14:54:48 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <vector>
# include <cctype>

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

#endif //UTILS_HPP
