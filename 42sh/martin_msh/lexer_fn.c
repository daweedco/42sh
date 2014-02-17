/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 12:20:02 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 16:27:54 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_minishell.h"

void			free_lex(t_lex *lexer)
{
	t_lexer		*lex;
	t_lexer		*tmp;

	lex = lexer->start;
	while (lex)
	{
		tmp = lex->next;
		free(lex->str);
		free(lex);
		lex = tmp;
	}
	free(lexer);
}

t_lex		*init_lex(void)
{
	t_lex		*new;

	if ((new = (t_lex *)malloc(sizeof(*new))) == NULL)
		exit(ft_print_error("malloc"));
	new->start = NULL;
	new->last = NULL;
	return (new);
}

void		free_node(t_lexer *del)
{
	if (del->str)
		free(del->str);
	free(del);
}

t_lexer		*new_node(void)
{
	t_lexer		*new;

	if ((new = (t_lexer *)malloc(sizeof(*new))) == NULL)
		exit(ft_print_error("malloc"));
	new->prev = NULL;
	new->next = NULL;
	new->str = NULL;
	new->type = 0;
	return (new);
}

int			browse_quote(char *ptr)
{
	int		ret;

	ret = 0;
	ptr++;
	while (*ptr != '\'' && *ptr != '\"' && *ptr)
	{
		ptr++;
		ret++;
	}
	if (!(*ptr))
		ret = 0;
	return (ret);
}
