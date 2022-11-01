# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/10/31 20:30:43 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex

MKF =		Makefile

FILES =		pipex.c			\
			get_comand.c	\
			parse_input.c

MKF =		Makefile

SRC =		$(addprefix $(SRC_DIR)/, $(FILES))

OBJ =		$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

DEPS =		$(addprefix $(DEPS_DIR)/, $(FILES:.o=.d))

SRC_DIR =	src

OBJ_DIR =	.obj

DEPS_DIR =	.deps

MAKE_LIB =	inc/bmlib/

LIB =		inc/bmlib/bmlib.a

INCLUDE =	-I inc/headers

INCLUDE +=	-I inc/bmlib

GCC =		gcc

FLAGS =		-Wall -Werror -Wextra -fsanitize=address

FLAGS_MMD =	-Wall -Werror -Wextra -MMD -MP