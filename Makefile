# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 02:33:06 by chaejkim          #+#    #+#              #
#    Updated: 2022/09/20 11:03:37 by hyko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = #-Wall -Werror -Wextra
SAN_FLAG = #-g3 -fsanitize=address

LFT = libft/libft.a
LOCAL_RL_DIR = /opt/homebrew/Cellar/readline/8.1.2
# CLUSTER_RL_DIR = $(HOME)/.brew/opt/readline
#CLUSTER_RL_DIR =  /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/readline

LDFLAGS="-L/Users/hyko/.brew/opt/readline/lib"
CPPFLAGS="-I/Users/hyko/.brew/opt/readline/include"

INC = -Iinclude -Ilibft -I$(CLUSTER_RL_DIR)/include
LIB = -Llibft -lft -L$(CLUSTER_RL_DIR)/lib -lreadline

#MAIN_SRC = $(addprefix src/main/, main.c readcmdline.c set_sigaction.c shell_sigaction.c)
#ENV_SRC = $(addprefix src/env/, env.c is_valid_env_name.c keylen.c)
#TOKEN_SRC = $(addprefix src/tokenizer/, token.c tokenizer.c)
#LEXER_SRC = $(addprefix src/lexer/, lexer.c)
#EXPANS_SRC = $(addprefix src/expansion/, expansion.c \
#			 parameter_expansion.c cmdpath_expansion.c input_file_checker.c)
#PARSER_SRC = $(addprefix src/parser/, parser.c tokens_to_cmds.c remove_quote.c)
#EXCUTOT_SRC = $(addprefix src/executor/, redirection.c)
#utils_SRC = $(addprefix src/utils/, main.c ft_error.c is_file_exist.c)
#TMP_SRC = $(addprefix src/tmp/, print.c)

#SRC = MAIN_SRC ENV_SRC TOKEN_SRC LEXER_SRC EXPANS_SRC PARSER_SRC EXCUTOT_SRC utils_SRC TMP_SRC

SRC = src/main/main.c \
	  src/main/readcmdline.c \
	  src/main/set_signal.c \
	  src/main/set_heredoc_signal.c \
	  src/env/env.c \
	  src/env/env_utils.c \
	  src/env/env_name_utils.c \
	  src/env/export.c \
	  src/tokenizer/token.c \
	  src/tokenizer/tokenizer.c \
	  src/lexer/lexer.c \
	  src/expansion/expansion.c \
	  src/expansion/do_expand.c \
	  src/expansion/attach_str.c \
	  src/parser/parser.c \
	  src/parser/tokens_to_cmds.c \
	  src/parser/remove_quote.c \
	  src/utils/ft_error.c \
	  src/utils/is_file_exist.c \
	  src/tmp/print.c \
	  src/executor/execute.c \
	  src/executor/execute_builtin.c \
	  src/executor/execute_err.c \
	  src/executor/is_path.c \
	  src/executor/cmd_to_path.c \
	  src/executor/make_arguments.c \
	  src/executor/redir_err.c \
	  src/executor/redirection.c \
	  src/builtin/builtin_env.c \
	  src/builtin/builtin_export.c \
	  src/builtin/builtin_export_utils.c \
	  src/builtin/builtin_unset.c \
	  src/builtin/builtin_echo.c \
	  src/builtin/builtin_cd.c \
	  src/builtin/builtin_pwd.c \
	  src/builtin/builtin_exit.c \
	  src/heredoc/heredoc.c \

#  src/exec/exec.c \
#  src/iostream/pipe.c \
#  src/iostream/redirect.c \
#  src/builtin/

OBJ = $(patsubst src%, obj%, $(SRC:.c=.o))

obj/%.o : src/%.c
	@$(CC) $(CFLAGS) $(SAN_FLAG) $(LDFLAGS) -Qunused-arguments $(CPPFLAGS) $(INC) -o $@ -c $<

all: $(LFT) obj $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(SAN_FLAG) $(LDFLAGS) -Qunused-arguments $(CPPFLAGS) -o $@ $^ $(LIB)

$(LFT):
	@$(MAKE) -s -C libft bonus

clean:
	@$(MAKE) -s -C libft $@
	rm -rf obj

fclean: clean
	@$(MAKE) -s -C libft $@
	@rm -rf $(NAME)

obj:
	@mkdir -p obj
	@mkdir -p obj/main
	@mkdir -p obj/builtin
	@mkdir -p obj/heredoc
	@mkdir -p obj/executor
	@mkdir -p obj/env
	@mkdir -p obj/expansion
	@mkdir -p obj/tokenizer
	@mkdir -p obj/lexer
	@mkdir -p obj/parser
	@mkdir -p obj/iostream
	@mkdir -p obj/exec
	@mkdir -p obj/utils
	@mkdir -p obj/tmp

re: fclean all

.PHONY: all clean fclean re
