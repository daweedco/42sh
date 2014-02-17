# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/12 19:04:52 by mle-roy           #+#    #+#              #
#    Updated: 2014/02/12 19:13:16 by mle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=romain_sh3
VERSION=1.0.0
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft -L /usr/lib -ltermcap

SRC=cd.c \
	edit_cmd.c \
	execute_cmd.c \
	execute_env.c \
	ft_env.c \
	ft_select.c \
	ft_strsplit_space.c \
	init_cmd.c \
	init_env.c \
	init_list.c \
	init_pipe.c \
	init_term.c \
	main.c \
	signal.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c minishell3.h ./libft/includes
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
