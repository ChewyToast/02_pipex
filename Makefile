# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/11 19:55:06 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -include utls/defines.mk
# -include utls/mandatory.mk
# -include utls/bonus.mk

NAME		=		pipex

FILES		=		pipex.c	\
					utils1.c\
					utils2.c

SRC			=		$(addprefix $(SRC_DIR)/, $(FILES))

OBJS		=		$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

DEPS_PIPEX	=		$(addprefix $(DEPS_DIR)/, $(OBJS:.o=.d))

SRC_DIR		=		src

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

all:
				@$(MAKE) -C $(MAKE_LIB)
				@$(MAKE) $(NAME)

clean:
				@rm -rf $(OBJ_DIR)
				@rm -rf $(DEPS_DIR)
				@echo "Deleting files .o and .d"

fclean:
				@$(MAKE) clean
				@rm -f $(NAME)
				@echo "Deleting pipex"

fcleanall:
				@$(MAKE) fclean -C $(MAKE_LIB)
				@$(MAKE) clean
				@rm -f $(NAME)
				@echo "Deleting pipex"

re:
				@$(MAKE) fclean
				@$(MAKE) all

$(NAME):		$(OBJ_DIR) $(DEPS_DIR) $(OBJS)
				@$(GCC) $(FLAGS) $(OBJS) $(LIB) -o $(NAME)
				@echo "pipex compiled 🎋"

$(OBJ_DIR):
				@mkdir -p -m700 $(OBJ_DIR)

$(DEPS_DIR):
				@mkdir -p -m700 $(DEPS_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(LIB) $(MKF)
				@$(GCC) $(FLAGS_MMD) $(INCLUDE) -c $< -o $@
				@echo "compilin pipex file: <$(notdir $<)>"
				@mv $(patsubst %.o, %.d, $@) $(DEPS_DIR)/

$(LIB):
				@$(MAKE) -C $(MAKE_LIB)

-include $(DEPS)

.PHONY:		all clean fclean fcleanall re
