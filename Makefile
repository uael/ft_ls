# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 09:52:36 by alucas-           #+#    #+#              #
#    Updated: 2017/11/18 19:59:34 by null             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = gcc
CC_FLAGS = -Wall -Werror -Wextra -I$(LFT_PATH)/include

LFT_PATH = ./libft/
LIB_PATH = ./lib/
SRC_PATH = ./src/
INC_PATH = ./include/ $(LFT_PATH)/include
OBJ_PATH = ./obj/

SRC = $(addprefix $(LIB_PATH),$(LIB_NAME))
LIB = $(addprefix $(LIB_PATH),$(LIB_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(LIBLS_OBJ_NAME)) \
	$(addprefix $(OBJ_PATH),$(LS_OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

LIBLS_OBJ_NAME = $(LIBLS_NAME:.c=.o)
LIBLS_NAME = entry.c ls.c print.c sort.c

LS_OBJ_NAME = $(LS_NAME:.c=.o)
LS_NAME = cli.c

all: $(NAME)

libls: $(OBJ)
	make -C $(LFT_PATH)
	ar -rc libls.a $?
	ranlib libls.a

$(NAME): libls
	$(CC) -o $(NAME) $(OBJ) -L$(LFT_PATH) -L. -lft -lls

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<

$(OBJ_PATH)%.o: $(LIB_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CC_FLAGS) $(INC) -o $@ -c $<

clean:
	make -C $(LFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LFT_PATH) fclean
	rm -f libls.a
	rm -f $(NAME)

check:
	@./test.sh

re: fclean all

.PHONY: all, $(NAME), clean, fclean, re
