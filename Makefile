# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/11 09:58:53 by tchartie          #+#    #+#              #
#    Updated: 2025/10/16 13:55:15 by tchartie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#============ NAME ============#

NAME				= 	scop

#========= COMPILATOR =========#

CC 				= 	c++

#=========== FLAGS ============#

INC_DIR			= 	./inc/ \
						./GLFW/include/GLFW/ \
						./inc/glad/.

GLFWARCHIVE		=	GLFW/build/src/libglfw3.a

INC_DIR			:=	$(addprefix -I, $(INC_DIR))

CFLAGS 			= 	-MP -MMD -Wall -Werror -Wextra -std=c++17

MAKEFLAGS		=	--no-print-directory

#=========== COLOR ============#

BASE_COLOR 		=	\033[0;39m
GRAY 				=	\033[0;90m
RED 				=	\033[0;91m
GREEN 			=	\033[0;92m
YELLOW 			=	\033[0;93m
BLUE 				=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN 				=	\033[0;96m
WHITE				=	\033[0;97m

#========== SOURCES ===========#

SRC_DIR 			= 	src/
SRC_NAME 		=	main.cpp

OBJ_DIR 			=	obj/
OBJ_NAME			=	$(SRC_NAME:.cpp=.o)
OBJ				=	$(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))

all:		glfw glad glm $(NAME)

glfw:
	@if ls | grep -q "GLFW"; then \
		echo "$(RED)GLFW Found $(BASE_COLOR)"; \
	else \
		echo "$(RED)GLFW Not Found $(BASE_COLOR)"; \
		echo "$(RED)Downloading GLFW from github  $(BASE_COLOR)"; \
		git clone https://github.com/glfw/glfw.git GLFW; \
		echo "$(RED)Compiling GLFW $(BASE_COLOR)"; \
		cmake -S GLFW -B GLFW/build; \
		cmake --build GLFW/build; \
	fi

glad:
	@if ls src | grep -q "glad"; then \
		echo "$(RED)glad Found $(BASE_COLOR)"; \
	else \
		echo "$(RED)glad Not Found $(BASE_COLOR)"; \
		echo "$(RED)Downloading glad from github  $(BASE_COLOR)"; \
		pip install glad; \
		git clone https://github.com/Dav1dde/glad.git glad; \
		python -m glad --out-path=glad/build --generator=c; \
		mkdir -p glad2; \
		cp glad/build/include/glad/glad.h glad2/.; \
		cp glad/build/src/glad.c glad2/.; \
		rm -rf glad; \
		mv glad2 glad; \
		mv glad/glad.c glad/glad.cpp; \
		mkdir -p src/glad; \
		mkdir -p inc/glad; \
		mv glad/glad.cpp src/glad/; \
		mv glad/glad.h inc/glad/; \
		rm -rf glad; \
	fi

glm:
	@if ls | grep -q "glm"; then \
		echo "$(RED)GLM Found $(BASE_COLOR)"; \
	else \
		echo "$(RED)GLM Not Found $(BASE_COLOR)"; \
		echo "$(RED)Cloning GLM from github $(BASE_COLOR)"; \
		git clone https://github.com/g-truc/glm.git glm; \
	fi

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GLFWARCHIVE) $(LDFLAGS)
	@echo "$(GREEN)scop successfully compiled! $(BASE_COLOR)"

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $< $(BASE_COLOR)"
	@$(CC) $(CFLAGS) $(INC_DIR) $< -c -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)scop objects files cleanned! $(BASE_COLOR)"

fclean:	clean
	@rm -f $(NAME)
	@echo "$(CYAN)scop executable file cleanned! $(BASE_COLOR)"

dclean: fclean
	@rm -rf src/glad
	@rm -rf inc/glad
	@rm -rf GLFW
	@rm -rf glm
	@echo "$(GREEN)Cleaned external libraries $(BASE_COLOR)"

re: 		fclean all

.PHONY :	all glwf glad glm clean fclean dclean re