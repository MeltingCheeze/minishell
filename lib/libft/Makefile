# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/05 19:28:38 by chaejkim          #+#    #+#              #
#    Updated: 2022/09/06 18:08:23 by hyko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

INC = -I.

SRC = $(addprefix src/, ft_toupper.c ft_tolower.c ft_isascii.c ft_isprint.c ft_isdigit.c \
	  ft_isalpha.c ft_isalnum.c ft_strncmp.c ft_strlen.c ft_strlcpy.c \
	  ft_memcpy.c ft_strchr.c ft_strrchr.c ft_strlcat.c ft_strnstr.c \
	  ft_memset.c ft_bzero.c ft_memchr.c ft_memmove.c ft_memcmp.c ft_atoi.c \
	  ft_strdup.c ft_strndup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	  ft_strcpy.c ft_strcmp.c ft_strchr.c \
	  ft_calloc.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_free_pptr.c \
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c)

BSRC = $(addprefix src/, ft_lstnew.c ft_lstadd_front.c \
	   ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	   ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_del_ptr.c)

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
