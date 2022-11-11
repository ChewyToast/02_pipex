# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mandatory.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 17:43:10 by bmoll-pe          #+#    #+#              #
#    Updated: 2022/11/11 19:28:19 by bmoll-pe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE_PIPEX		=	pipex.c		\
					utils1.c	\
					utils2.c

SRC			=		$(addprefix $(SRC_DIR)/, $(FILES))

OBJS		=		$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

DEPS_PIPEX	=		$(addprefix $(DEPS_DIR)/, $(OBJS:.o=.d))

SRC_DIR		=		src