# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/22 02:33:06 by chaejkim          #+#    #+#              #
#    Updated: 2022/09/24 15:23:26 by chaejkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
SAN_FLAG = #-g3 -fsanitize=address

LFT = libft/libft.a
LOCAL_RL_DIR = /opt/homebrew/opt/readline
CLUSTER_RL_DIR = $(HOME)/.brew/opt/readline

# local mac
# INC = -Iinclude -Ilibft -I$(LOCAL_RL_DIR)/include
# LIB = -Llibft -lft -L$(LOCAL_RL_DIR)/lib -lreadline

INC = -Iinclude -Ilibft -I$(CLUSTER_RL_DIR)/include
LIB = -Llibft -lft -L$(CLUSTER_RL_DIR)/lib -lreadline

MAIN_SRC = $(addprefix src/main/, main.c readcmdline.c set_signal.c)
ENV_SRC = $(addprefix src/env/, env.c env_utils.c env_name_utils.c export.c env_del.c)
UTILS_SRC = $(addprefix src/utils/,ft_error.c file_stat.c set_quote.c)
PARSER_SRC = $(addprefix src/parser/, parser.c script.c tokens_to_cmds.c remove_quote.c)
TOKEN_SRC = $(addprefix src/tokenizer/, token.c tokenizer.c)
LEXER_SRC = $(addprefix src/lexer/, lexer.c)
EXPANS_SRC = $(addprefix src/expansion/, expansion.c expansion_utils.c)
REDIRECTION_SRC = $(addprefix src/redirection/, redir_heredoc.c redir_err.c redirection.c redir_utils.c)
EXCUTOT_SRC = $(addprefix src/executor/, execute.c exec_builtin.c exec_err.c \
				exec_child.c exec_parent.c exec_utils.c)
BUILTIN_SRC = $(addprefix src/builtin/, builtin_env.c builtin_export.c builtin_export_utils.c \
			  builtin_unset.c builtin_echo.c builtin_cd.c builtin_pwd.c builtin_exit.c)

SRC = $(MAIN_SRC) $(ENV_SRC) $(UTILS_SRC) $(TMP_SRC) \
	  $(PARSER_SRC) $(TOKEN_SRC) $(LEXER_SRC) $(EXPANS_SRC) \
	  $(REDIRECTION_SRC) $(BUILTIN_SRC) $(EXCUTOT_SRC) 

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
	@mkdir -p obj/redirection
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
