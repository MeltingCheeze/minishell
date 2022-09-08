# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 02:33:06 by chaejkim          #+#    #+#              #
#    Updated: 2022/09/08 20:00:39 by chaejkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
SAN_FLAG = -g3 -fsanitize=address

LFT = lib/libft/libft.a
LOCAL_RL_DIR = /opt/homebrew/Cellar/readline/8.1.2
CLUSTER_RL_DIR = $(HOME)/.brew/opt/readline
#CLUSTER_RL_DIR =  /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/readline

INC = -Iinclude -Ilib/libft -I$(CLUSTER_RL_DIR)/include
LIB = -Llib/libft -lft -L$(CLUSTER_RL_DIR)/lib -lreadline

#MAIN_SRC = $(addprefix src/main/, main.c readcmdline.c set_sigaction.c shell_sigaction.c)
#ENV_SRC = $(addprefix src/env/, env.c is_valid_env_name.c keylen.c)
#TOKEN_SRC = $(addprefix src/tokenizer/, token.c tokenizer.c)
#LEXER_SRC = $(addprefix src/lexer/, lexer.c)
#EXPANS_SRC = $(addprefix src/expansion/, expansion.c \
#			 parameter_expansion.c cmdpath_expansion.c input_file_checker.c)
#PARSER_SRC = $(addprefix src/parser/, parser.c tokens_to_cmds.c remove_quote.c)
#EXCUTOT_SRC = $(addprefix src/executor/, redirection.c)
#UTILE_SRC = $(addprefix src/utile/, main.c ft_error.c is_file_exist.c)
#TMP_SRC = $(addprefix src/tmp/, print.c)

#SRC = MAIN_SRC ENV_SRC TOKEN_SRC LEXER_SRC EXPANS_SRC PARSER_SRC EXCUTOT_SRC UTILE_SRC TMP_SRC

SRC = src/main/main.c \
	  src/main/readcmdline.c \
	  src/main/set_signal.c \
	  src/main/signal_handler.c \
	  src/env/env.c \
	  src/env/is_valid_env_name.c \
	  src/env/keylen.c \
	  src/tokenizer/token.c \
	  src/tokenizer/tokenizer.c \
	  src/lexer/lexer.c \
	  src/expansion/expansion.c \
	  src/expansion/parameter_expansion.c \
	  src/parser/parser.c \
	  src/parser/tokens_to_cmds.c \
	  src/parser/remove_quote.c \
	  src/utile/ft_error.c \
	  src/utile/is_file_exist.c \
	  src/tmp/print.c \
	  src/executor/execute.c \
	  src/executor/check_cmdpath.c \
	  src/executor/heredoc_execute.c \
	  src/executor/redirection.c

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
	@mkdir -p obj/executor
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
