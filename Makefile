# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/12/06 21:48:33 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

NAME_BNS	=	pipex_bonus

MANDATORY	=	.mandatory

BONUSS		=	.bonus

#	-------------------- Mandatory --------------------
FILES		=	pipex.c			utils1.c		utils2.c	\
				ft_cmd_split.c	ft_split_utils.c

SRC			=	$(addprefix $(SRC_DIR)/, $(FILES))

OBJS		=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

DEPS_PIPEX	=	$(addprefix $(DEPS_DIR)/, $(FILES:.c=.d))

SRC_DIR		=	mandatory

#	-------------------- Bonus --------------------
FILES_BNS	=	pipex_bonus.c			utils1_bonus.c		utils2_bonus.c	\
				ft_cmd_split_bonus.c	ft_split_utils_bonus.c

SRC_BNS		=	$(addprefix $(SRC_DIR)/, $(FILES_BNS))

OBJS_BNS	=	$(addprefix $(OBJ_DIR)/, $(FILES_BNS:.c=.o))

DEPS_PIPEX_BNS	=	$(addprefix $(DEPS_DIR)/, $(FILES_BNS:.c=.d))

SRC_DIR_BNS		=	bonus

#	---------------------

MKF			=	Makefile

OBJ_DIR		=	.obj

DEPS_DIR	=	.deps

MAKE_LIB	=	inc/bmlib/

LIB			=	inc/bmlib/bmlib.a

INCLUDE		=	-I inc/headers

INCLUDE		+=	-I inc/bmlib

GCC			=	gcc

FLAGS		=	-Wall -Werror -Wextra

FLAGS_MMD	=	-Wall -Werror -Wextra -MMD -MP

GSU =			git submodule update

GSU_FLAGS =		--remote --merge --recursive

DEL_LINE	=	\033[2K

DEF_COLOR	=	\033[0;39m

BROWN		=	\033[38;2;184;143;29m

DARK_GRAY	=	\033[38;5;234m

DARK_GREEN	=	\033[1m\033[38;2;75;179;82m

all:
				@$(MAKE) -C $(MAKE_LIB)
				@$(MAKE) $(MANDATORY)

update:
				@$(MAKE) update -C $(MAKE_LIB)
				@$(GSU) $(GSU_FLAGS)

bonus:
				@$(MAKE) -C $(MAKE_LIB)
				@$(MAKE) $(BONUSS)

clean:
				@rm -rf $(OBJ_DIR)
				@rm -rf $(DEPS_DIR)
				@echo "Deleting files .o and .d"

fclean:
				@$(MAKE) clean
				@rm -f $(MANDATORY) $(BONUSS)
				@rm -f $(NAME) $(NAME_BNS)
				@echo "Deleting pipex"

fcleanall:
				@$(MAKE) fclean -C $(MAKE_LIB)
				@$(MAKE) clean
				@rm -f $(MANDATORY) $(BONUSS)
				@rm -f $(NAME) $(NAME_BNS)
				@echo "Deleting pipex"

re:
				@$(MAKE) fclean
				@$(MAKE) all

$(MANDATORY):	$(OBJ_DIR) $(DEPS_DIR) $(OBJS)
				@$(GCC) $(FLAGS) $(OBJS) $(LIB) -o $(NAME)
				@touch $(MANDATORY)
				@echo "pipex compiled 🎋"

$(BONUSS):		$(OBJ_DIR) $(DEPS_DIR) $(OBJS_BNS)
				@$(GCC) $(FLAGS) $(OBJS_BNS) $(LIB) -o $(NAME)
				@touch $(BONUSS)
				@echo "pipex compiled 🎋"

$(OBJ_DIR):
				@mkdir -p -m700 $(OBJ_DIR)

$(DEPS_DIR):
				@mkdir -p -m700 $(DEPS_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(LIB) $(MKF)
				@$(GCC) $(FLAGS_MMD) $(INCLUDE) -c $< -o $@
				@echo "compilin pipex file: <$(notdir $<)>"
				@mv $(patsubst %.o, %.d, $@) $(DEPS_DIR)/

$(OBJ_DIR)/%.o:	$(SRC_DIR_BNS)/%.c $(LIB) $(MKF)
				@$(GCC) $(FLAGS_MMD) $(INCLUDE) -c $< -o $@
				@echo "compilin pipex file: <$(notdir $<)>"
				@mv $(patsubst %.o, %.d, $@) $(DEPS_DIR)/

$(LIB):
				@$(MAKE) -C $(MAKE_LIB)

-include $(DEPS_PIPEX)
-include $(DEPS_PIPEX_BNS)

.PHONY:	all bonus update clean fclean fcleanall re
