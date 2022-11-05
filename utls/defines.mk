# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    defines.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/05 01:10:58 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				pipex

MKF =				Makefile

FILE_PIPEX =		pipex.c

FILES_PARSING =		parse_first_part.c	\
					parse_second_part.c	\
					parse_third_part.c	\
					parse_input.c		\
					parse_utils.c		\
					get_inputs.c

MKF =				Makefile

SRC_PIPEX =			$(addprefix $(SRC_DIR)/, $(FILE_PIPEX))

SRC_PARSING =		$(addprefix $(SRC_DIR_PARSE)/, $(FILES_PARSING))

OBJ_PIPEX =			$(addprefix $(OBJ_DIR)/, $(FILE_PIPEX:.c=.o))

OBJ_PARSING =		$(addprefix $(OBJ_DIR)/, $(FILES_PARSING:.c=.o))

DEPS_PIPEX =		$(addprefix $(DEPS_DIR)/, $(FILES:.o=.d))

DEPS_PARSING =		$(addprefix $(DEPS_DIR)/, $(FILES_PARSING:.o=.d))

SRC_DIR =			src

SRC_DIR_PARSE =		src/parsing

OBJ_DIR =			.obj

DEPS_DIR =			.deps

MAKE_LIB =			inc/bmlib/

LIB =				inc/bmlib/bmlib.a

INCLUDE =			-I inc/headers

INCLUDE +=			-I inc/bmlib

GCC =				gcc

FLAGS =				-Wall -Werror -Wextra

FLAGS_MMD =			-Wall -Werror -Wextra -MMD -MP