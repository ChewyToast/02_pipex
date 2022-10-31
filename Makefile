# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/10/31 21:06:38 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
-include utls/defines.mk

all:
				@$(MAKE) -C $(MAKE_LIB)
				@$(MAKE) $(NAME)

clean:
				@rm -rf $(OBJ_DIR)
				@rm -rf $(DEPS_DIR)

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


$(NAME):		$(OBJ_DIR) $(DEPS_DIR) $(OBJ)
				$(GCC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

$(OBJ_DIR):
				mkdir -p -m777 $(OBJ_DIR)

$(DEPS_DIR):
				mkdir -p -m777 $(DEPS_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(LIB) $(MKF)
				$(GCC) $(FLAGS_MMD) -I $(MAKE_LIB) -c $< -o $@
				@mv $(patsubst %.o, %.d, $@) $(DEPS_DIR)/

$(LIB):
				@$(MAKE) -C $(MAKE_LIB)

-include $(DEPS)

.PHONY:		all clean fclean re
