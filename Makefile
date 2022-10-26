# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/10/26 21:12:17 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex

MKF =		Makefile

SRC =		pruebas.c

OBJ =		$(SRC:%.c=%.o)

DEPS =		$(SRC:%.c=%.d)

SRC_DIR =	src/

OBJ_DIR =	obj/

MAKE_LIB =	inc/bmlib/

LIB =		inc/bmlib/bmlib.a

GCC =		gcc

FLAGS =		-Wall -Werror -Wextra -fsanitize=address

FLAGS_MMD =	-Wall -Werror -Wextra -MMD -MP

all:
			@$(MAKE) $(NAME)

$(NAME):	$(OBJ_DIR) $(OBJ)
			@$(GCC) $(FLAGS) $(OBJ_DIR)$(OBJ) $(LIB) -o $(NAME)

$(LIB):
			@$(MAKE) -C $(MAKE_LIB)

$(OBJ_DIR):
			@mkdir $@

clean:
			@rm -rf $(OBJ_DIR)
			@rm -f $(OBJ_DIR)$(OBJ)
			@rm -f $(OBJ_DIR)$(DEPS)

fclean:
			@$(MAKE) clean
			@rm -f $(NAME)

fcleanall:
			@$(MAKE) fclean -C $(MAKE_LIB)
			@$(MAKE) clean
			@rm -f $(NAME)

re:
			@$(MAKE) fclean
			@$(MAKE) all

%.o:		$(SRC_DIR)%.c $(LIB)
			@$(GCC) $(FLAGS_MMD) -I inc/bmlib/ -c $< -o $@
			@mv $@ $(OBJ_DIR)
			@mv $(DEPS) $(OBJ_DIR)

.PHONY:		all clean fclean re
