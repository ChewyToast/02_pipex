# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bonus.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 17:43:53 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/11 17:47:06 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_BONUS			=		pipex

FILE_PIPEX_BONUS	=		pipex_bonus.c

FILES_UTILS_BONUS	=		utils1_bonus.c	\
							utils2_bonus.c

FILES_PARTS_BONUS	=		first_part_bonus.c	\
							third_part_bonus.c

SRC_PIPEX_BONUS		=		$(addprefix $(SRC_DIR_BONUS)/, $(FILE_PIPEX_BONUS))

SRC_UTILS_BONUS		=		$(addprefix $(SRC_DIR_BONUS)/$(SRC_UTILS_BONUS)/, $(FILES_UTILS_BONUS))

SRC_PARTS_BONUS		=		$(addprefix $(SRC_DIR_BONUS)/$(SRC_PARTS_BONUS)/, $(FILES_PARTS_BONUS))

OBJS_BONUS			=		$(addprefix $(OBJ_DIR_BONUS)/, $(FILE_PIPEX_BONUS:.c=.o))

OBJS_BONUS			+=		$(addprefix $(OBJ_DIR_BONUS)/, $(FILES_UTILS_BONUS:.c=.o))

OBJS_BONUS			+=		$(addprefix $(OBJ_DIR_BONUS)/, $(FILES_PARTS_BONUS:.c=.o))

DEPS_PIPEX_BONUS	=		$(addprefix $(DEPS_DIR_BONUS)/, $(OBJS_BONUS:.o=.d))

SRC_DIR_BONUS		=		src_bonus

UTILS_DIR_BONUS		=		utils

PARTS_DIR_BONUS		=		parts