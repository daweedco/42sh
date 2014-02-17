/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 17:40:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/13 19:48:35 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

#include <stdio.h> //nonon

void		debug_print_lex(t_lx *lex)
{
	t_lexer		*token;
	int			i;

	token = lex->first;
	i = 1;
	while (token)
	{
		printf("token[%d][t=%d][%s]\n", i, token->type, token->str);
		i++;
		token = token->next;
	}
}


int		main(int argc, char **argv)
{
	char			*cmd;
	t_lx			*lex;
	extern char		**environ;

	if (argc != 2)
	{
		write(1, "essayes encore\n", 15);
		return (0);
	}
	cmd = ft_strdup(argv[1]);
	printf("CMD=%s\n", cmd);
	sh_lexer(&lex, &cmd, environ);
	debug_print_lex(lex);
	return (0);
}
