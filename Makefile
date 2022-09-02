# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 02:33:06 by chaejkim          #+#    #+#              #
#    Updated: 2022/09/03 02:34:43 by chaejkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
SAN_FLAG = -g3 -fsanitize=address

LFT = lib/libft/libft.a
LOCAL_RL_DIR = /opt/homebrew/Cellar/readline/8.1.2
CLUSTER_RL_DIR = $(HOME)/.brew/opt/readline

INC = -Iinclude -Ilib/libft -I$(CLUSTER_RL_DIR)/include
LIB = -Llib/libft -lft -L$(CLUSTER_RL_DIR)/lib -lreadline

SRC = src/main/main.c \
	  src/main/readcmdline.c \
	  src/main/set_sigaction.c \
	  src/main/shell_sigaction.c \
	  src/env/env.c \
	  src/tokenizer/token.c \
	  src/tokenizer/tokenizer.c \
	  src/lexer/lexer.c \
	  src/expansion/expansion.c \
	  src/expansion/parameter_expansion.c \
	  src/parser/parser.c \
	  src/utile/ft_error.c \
	  src/tmp/print.c

#  src/exec/exec.c \
#  src/iostream/pipe.c \
#  src/iostream/redirect.c \
#  src/builtins/

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
	@mkdir -p obj/expansion
	@mkdir -p obj/tokenizer
	@mkdir -p obj/lexer
	@mkdir -p obj/parser
	@mkdir -p obj/iostream
	@mkdir -p obj/exec
	@mkdir -p obj/utile
	@mkdir -p obj/tmp

re: fclean all

.PHONY: all clean fclean re
