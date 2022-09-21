# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 02:33:06 by chaejkim          #+#    #+#              #
#    Updated: 2022/09/21 20:21:47 by chaejkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = #-Wall -Werror -Wextra
SAN_FLAG = -g3 -fsanitize=address

LFT = libft/libft.a
LOCAL_RL_DIR = /opt/homebrew/opt/readline
CLUSTER_RL_DIR = $(HOME)/.brew/opt/readline

# local mac
# INC = -Iinclude -Ilibft -I$(LOCAL_RL_DIR)/include
# LIB = -Llibft -lft -L$(LOCAL_RL_DIR)/lib -lreadline

INC = -Iinclude -Ilibft -I$(CLUSTER_RL_DIR)/include
LIB = -Llibft -lft -L$(CLUSTER_RL_DIR)/lib -lreadline

MAIN_SRC = $(addprefix src/main/, main.c readcmdline.c set_signal.c set_heredoc_signal.c)
ENV_SRC = $(addprefix src/env/, env.c env_utils.c env_name_utils.c export.c)
UTILS_SRC = $(addprefix src/utils/,ft_error.c is_file_exist.c)
TMP_SRC = $(addprefix src/tmp/, print.c)
PARSER_SRC = $(addprefix src/parser/, parser.c tokens_to_cmds.c remove_quote.c)
TOKEN_SRC = $(addprefix src/tokenizer/, token.c tokenizer.c)
LEXER_SRC = $(addprefix src/lexer/, lexer.c)
EXPANS_SRC = $(addprefix src/expansion/, expansion.c expansion_utils.c)
HEREDOC_SRC = $(addprefix src/heredoc/, heredoc.c)
EXCUTOT_SRC = $(addprefix src/executor/, execute.c execute_builtin.c execute_err.c \
			  is_path.c cmd_to_path.c make_arguments.c redir_err.c redirection.c)
BUILTIN_SRC = $(addprefix src/builtin/, builtin_env.c builtin_export.c builtin_export_utils.c \
			  builtin_unset.c builtin_echo.c builtin_cd.c builtin_pwd.c builtin_exit.c)

SRC = $(MAIN_SRC) $(ENV_SRC) $(UTILS_SRC) $(TMP_SRC) \
	  $(PARSER_SRC) $(TOKEN_SRC) $(LEXER_SRC) $(EXPANS_SRC) \
	  $(HEREDOC_SRC) $(BUILTIN_SRC) $(EXCUTOT_SRC) 

OBJ = $(patsubst src%, obj%, $(SRC:.c=.o))

obj/%.o : src/%.c
	@$(CC) $(CFLAGS) $(SAN_FLAG) -Qunused-arguments $(INC) -o $@ -c $<

all: $(LFT) obj $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(SAN_FLAG) -Qunused-arguments -o $@ $^ $(LIB)

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
