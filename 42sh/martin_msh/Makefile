# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/05 18:44:17 by mle-roy           #+#    #+#              #
#    Updated: 2014/02/05 18:44:17 by mle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=new_msh3_bit
VERSION=1.0.5
CFLAGS=-Wall -Werror -Wextra -g
INCLUDES=-I ./libft/includes
LIBS=-L ./libft -l ft

SRC=builtin_cd.c \
	builtin_env.c \
	builtin_exit.c \
	builtin_setenv.c \
	builtin_unsetenv.c \
	env_fn.c \
	exec_pipe.c \
	free_fn.c \
	ft_print_error.c \
	ft_setenv.c \
	ft_strsplitspace.c \
	lexer_fn.c \
	minishell1.c \
	msh_builtin.c \
	msh_check_access.c \
	msh_exec.c \
	msh_lexer.c \
	msh_parseur.c \
	msh_redir.c \
	msh_signal.c \
	parseur_append.c \
	parseur_fn1.c \
	parseur_init.c \
	parseur_lex.c \
	parseur_redir.c \
	print_parsed_tree.c \
	redir_append.c \
	builtin_echo.c \

OBJ=$(SRC:.c=.o)

all: build $(NAME) finish

build:
	@($(MAKE) -C ./libft)

$(NAME): $(OBJ) ./libft/libft.a
	gcc $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

%.o: %.c ft_minishell.h ./libft/includes
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

