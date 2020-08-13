# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/12 14:31:24 by mlacombe          #+#    #+#              #
#    Updated: 2020/08/13 22:55:21 by mlacombe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# program name
NAME			=wolf3d

# compiler
CC				=gcc
override CFLAGS	+=-Wall -Wextra -g3
PACKAGES		=pkg-config --cflags --libs sdl2
OBJ				=$(addprefix $(OBJ_DIR),$(SRC:.c=.o))
DEP				=$(addprefix $(OBJ_DIR),$(SRC:.c=.d))

# files
SRC				=main.c

# directories
SRC_DIR			=./srcs/
INC_DIR			=./includes/
OBJ_DIR			=./objects/

# ft library
FT				=./libft/
FT_LIB			=$(addprefix $(FT),libft.a)
FT_INC			=-I ./libft/includes
FT_LNK			=-L ./libft -l ft

all:
	$(MAKE) $(NAME)

-include $(DEP)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INC_DIR) -MMD -o $@ -c $<

$(FT_LIB): FORCE
	$(MAKE) -C $(FT)

$(MLX_LIB):
	$(MAKE) -C $(MLX)

$(NAME): $(OBJ) $(FT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) $(FT_LNK) -MMD -lm -o $(NAME)

norm:
	norminette ./srcs/*
	norminette ./includes/*
	$(MAKE) CFLAGS+= -Wpadded

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(FT) clean

fclean:
	$(MAKE) -C $(FT) fclean
	rm -rf $(OBJ_DIR) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

FORCE:

.PHONY : all clean fclean re FORCE
