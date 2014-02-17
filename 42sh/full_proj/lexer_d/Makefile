# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/14 15:53:27 by mle-roy           #+#    #+#              #
#    Updated: 2014/02/14 16:16:04 by dcohen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=full_proj
VERSION=1.0.5
CFLAGS=-Wall -Werror -Wextra -g3
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft

SRC=debug_print_lexer.c \
	lex_first_step.c \
	lex_fn1.c \
	lex_make.c \
	sh_lexer.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c lexer.h ./libft/includes
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAME))
	@($(MAKE) -C ./libft fclean)

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

.PHONY: all build clean fclean re v

