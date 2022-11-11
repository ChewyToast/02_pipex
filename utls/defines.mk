# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    defines.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/11 17:43:31 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MKF			=		Makefile

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