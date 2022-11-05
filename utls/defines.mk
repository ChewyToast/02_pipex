# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    defines.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/05 03:34:01 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		pipex

MKF			=		Makefile

FILE_PIPEX		=	pipex.c

FILES_PARSE	=		parse_input.c	\
					parse_utils.c	\
					get_inputs.c

FILES_PARTS	=		first_part.c	\
					second_part.c	\
					third_part.c	\

SRC_PIPEX	=		$(addprefix $(SRC_DIR)/, $(FILE_PIPEX))

SRC_PARSE	=		$(addprefix $(SRC_DIR)/$(SRC_PARSE)/, $(FILES_PARSE))

SRC_PARTS	=		$(addprefix $(SRC_DIR)/$(SRC_PARTS)/, $(FILES_PARTS))

OBJS		=		$(addprefix $(OBJ_DIR)/, $(FILE_PIPEX:.c=.o))

OBJS		+=		$(addprefix $(OBJ_DIR)/, $(FILES_PARSE:.c=.o))

OBJS		+=		$(addprefix $(OBJ_DIR)/, $(FILES_PARTS:.c=.o))

DEPS_PIPEX	=		$(addprefix $(DEPS_DIR)/, $(OBJS:.o=.d))

SRC_DIR		=		src

PARSE_DIR	=		parse

PARTS_DIR	=		parts

OBJ_DIR		=		.obj

DEPS_DIR	=		.deps

MAKE_LIB	=		inc/bmlib/

LIB			=		inc/bmlib/bmlib.a

INCLUDE		=		-I inc/headers

INCLUDE		+=		-I inc/bmlib

GCC			=		gcc

FLAGS		=		-Wall -Werror -Wextra

FLAGS_MMD	=		-Wall -Werror -Wextra -MMD -MP