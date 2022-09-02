# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 19:28:38 by chaejkim          #+#    #+#              #
#    Updated: 2022/09/02 21:38:22 by chaejkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

INC = -I.

SRC = src/ft_toupper.c src/ft_tolower.c src/ft_isascii.c src/ft_isprint.c src/ft_isdigit.c \
	  src/ft_isalpha.c src/ft_isalnum.c src/ft_strncmp.c src/ft_strlen.c src/ft_strlcpy.c \
	  src/ft_memcpy.c src/ft_strchr.c src/ft_strrchr.c src/ft_strlcat.c src/ft_strnstr.c \
	  src/ft_memset.c src/ft_bzero.c src/ft_memchr.c src/ft_memmove.c src/ft_memcmp.c src/ft_atoi.c \
	  src/ft_strdup.c src/ft_strndup.c src/ft_substr.c src/ft_strjoin.c src/ft_strtrim.c src/ft_split.c \
	  src/ft_strcpy.c src/ft_strcmp.c src/ft_strchr.c \
	  src/ft_calloc.c src/ft_itoa.c src/ft_strmapi.c src/ft_striteri.c src/ft_free_pptr.c \
	  src/ft_putchar_fd.c src/ft_putstr_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c

BSRC = src/ft_lstnew.c src/ft_lstadd_front.c src/ft_lstsize.c src/ft_lstlast.c src/ft_lstadd_back.c src/ft_lstdelone.c \
	   src/ft_lstclear.c src/ft_lstiter.c src/ft_lstmap.c src/ft_del_ptr.c

OBJ = $(patsubst src%, obj%, $(SRC:.c=.o))
BOBJ = $(patsubst src%, obj%, $(BSRC:.c=.o))

ifdef BONUS_FLAG
	OBJ_SWITCH = $(OBJ) $(BOBJ)
else
	OBJ_SWITCH = $(OBJ)
endif

all: obj $(NAME)

obj/%.o : src/%.c
	$(CC) $(CFLAGS) $(INC) $< -o $@

$(NAME): $(OBJ_SWITCH)
	ar -cr $@ $^

obj:
	@mkdir -p obj

clean:
	rm -rf obj

bonus:
	$(MAKE) BONUS_FLAG=1 all

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	@norminette $(SRC) $(BSRC)
	@norminette libft.h

.PHONY: all clean bonus fclean re
