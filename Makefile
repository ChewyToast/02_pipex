# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 18:59:54 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/09 21:59:01 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include utls/defines.mk

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

$(OBJ_DIR)/%.o:	$(SRC_DIR)/$(UTILS_DIR)/%.c $(LIB) $(MKF)
				@$(GCC) $(FLAGS_MMD) $(INCLUDE) -c $< -o $@
				@echo "compilin pipex file: <$(notdir $<)>"
				@mv $(patsubst %.o, %.d, $@) $(DEPS_DIR)/

$(OBJ_DIR)/%.o:	$(SRC_DIR)/$(PARTS_DIR)/%.c $(LIB) $(MKF)
				@$(GCC) $(FLAGS_MMD) $(INCLUDE) -c $< -o $@
				@echo "compilin pipex file: <$(notdir $<)>"
				@mv $(patsubst %.o, %.d, $@) $(DEPS_DIR)/

$(LIB):
				@$(MAKE) -C $(MAKE_LIB)

-include $(DEPS)

.PHONY:		all clean fclean fcleanall re
