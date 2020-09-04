# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlacombe <mlacombe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/12 14:31:24 by mlacombe          #+#    #+#              #
#    Updated: 2020/09/04 13:52:58 by mlacombe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# program name
NAME			=wolf3d

# compiler
CC				=gcc
override CFLAGS	+=-Wall -Wextra -g3
OBJ				=$(addprefix $(OBJ_DIR),$(SRC:.c=.o))
DEP				=$(addprefix $(OBJ_DIR),$(SRC:.c=.d))
FRAMEWORK		= SDL2 SDL2_ttf SDL2_image
FRAMEWORK_PATH	= frameworks
INCLUDE			=$(INC_DIR:%=-I %) $(FRAMEWORK:%=-I $(FRAMEWORK_PATH)/%.framework/Headers/)

# files
SRC				=	main.c				\
					file_management.c	\
					player.c			\
					engine.c			\
					raycaster.c			\
					hook.c

# directories
SRC_DIR			=./srcs/
INC_DIR			=./includes/ /usr/include/SDL2
OBJ_DIR			=./objects/

# ft library
FT				=./libft/
FT_LIB			=$(addprefix $(FT),libft.a)
FT_INC			=-I ./libft/includes
FT_LNK			=-L ./libft -l ft

ifeq ($(shell uname 2>/dev/null),Darwin) # Mac OS X
	LIB := -rpath @loader_path/$(FRAMEWORK_PATH) $(addprefix -framework ,$(FRAMEWORK)) $(FRAMEWORK_PATH:%=-F %) -lm
endif
ifeq ($(shell uname 2>/dev/null),Linux) # LINUX
	LIB := $(addprefix -l,$(FRAMEWORK)) -lm
endif

all:
	$(MAKE) $(NAME)

$(NAME): $(OBJ) $(FT_LIB)
	$(CC) $(CFLAGS) $(INCLUDE) $(FT_LNK) $(OBJ) -o $@ $(LIB)

-include $(DEP)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(FT_INC) $(INCLUDE) -MMD -c $< -o $@

$(FT_LIB): FORCE
	$(MAKE) -C $(FT)

norm:
	norminette ./srcs/*
	norminette ./includes/*.h
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
