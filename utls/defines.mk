# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    defines.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/09 22:58:35 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		pipex

MKF			=		Makefile

FILE_PIPEX		=	pipex.c

FILES_UTILS	=		utils1.c	\
					utils2.c

FILES_PARTS	=		first_part.c	\
					second_part.c	\
					third_part.c

SRC_PIPEX	=		$(addprefix $(SRC_DIR)/, $(FILE_PIPEX))

SRC_UTILS	=		$(addprefix $(SRC_DIR)/$(SRC_UTILS)/, $(FILES_UTILS))

SRC_PARTS	=		$(addprefix $(SRC_DIR)/$(SRC_PARTS)/, $(FILES_PARTS))

OBJS		=		$(addprefix $(OBJ_DIR)/, $(FILE_PIPEX:.c=.o))

OBJS		+=		$(addprefix $(OBJ_DIR)/, $(FILES_UTILS:.c=.o))

OBJS		+=		$(addprefix $(OBJ_DIR)/, $(FILES_PARTS:.c=.o))

DEPS_PIPEX	=		$(addprefix $(DEPS_DIR)/, $(OBJS:.o=.d))

SRC_DIR		=		src

UTILS_DIR	=		utils

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

DEL_LINE =			\033[2K

DEF_COLOR =			\033[0;39m

BROWN =				\033[38;2;184;143;29m

DARK_GRAY =			\033[38;5;234m

DARK_GREEN =		\033[1m\033[38;2;75;179;82m