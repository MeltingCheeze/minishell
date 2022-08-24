# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 02:33:06 by chaejkim          #+#    #+#              #
#    Updated: 2022/08/23 05:50:39 by chaejkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
SAN_FLAG = -g3 -fsanitize=address

LFT = lib/libft/libft.a

INC = -Iinclude -Ilib/libft
LIB = -Llib/libft -lft -lreadline

SRC = src/main/minishell.c \
	  src/main/signal.c \
	  src/env/env.c \
	  src/iostream/readcmdline.c \
	  src/parse/parse.c \
	  src/parse/token.c \
	  src/parse/tokenizer.c \
	  src/utile/ft_error.c

#  src/exec/exec.c \
#  src/iostream/pipe.c \
#  src/iostream/redirect.c \
#  src/builtins//

OBJ = $(patsubst src%, obj%, $(SRC:.c=.o))

obj/%.o : src/%.c
	@$(CC) $(CFLAGS) $(SAN_FLAG) $(INC) -o $@ -c $<

all: $(LFT) obj $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(SAN_FLAG) -o $@ $^ $(LIB)

$(LFT):
	@$(MAKE) -s -C lib/libft

clean:
	@$(MAKE) -s -C lib/libft $@
	rm -rf obj

fclean: clean
	@$(MAKE) -s -C lib/libft $@
	@rm -rf $(NAME)

obj:
	@mkdir -p obj
	@mkdir -p obj/main
	@mkdir -p obj/builtins
	@mkdir -p obj/env
	@mkdir -p obj/exec
	@mkdir -p obj/iostream
	@mkdir -p obj/parse
	@mkdir -p obj/utile

re: fclean all

.PHONY: all clean fclean re
