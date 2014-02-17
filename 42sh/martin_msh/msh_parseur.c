/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parseur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 18:32:41 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 14:53:05 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_minishell.h"
#include "libft.h"

static t_parse		*browse_lex(t_lexer *lex, char ***env)
{
	t_parse		*tree;

	tree = init_parse(env);
	while (lex)
	{
		if (lex->type == S_C && lex->next == NULL)
			break ;
		else if (lex->type == S_C)
			add_cmd_tree(tree);
		else if (lex->type == CMD && lex->prev && lex->prev->type > 3)
			add_redir_append(tree, lex);
		else if (lex->type == CMD && lex->prev && lex->prev->type == CMD)
			cat_inst_tree(tree, lex);
		else if (lex->type == CMD)
			add_inst_tree(tree, lex);
		lex = lex->next;
	}
	return (tree);
}

static int			first_check(t_lex *lexer)
{
	t_lexer		*tmp;

	tmp = lexer->start;
	if (tmp->type == PIPE || tmp->type == APPEND)
		return (parse_error(tmp->str));
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == S_C && tmp->next == NULL)
			break ;
		if (tmp->type > 1 && tmp->next == NULL)
			return (parse_error(tmp->str));
		if (tmp->type == S_C && (tmp->prev->type > 1 || tmp->next->type > 1))
			return (parse_error(tmp->str));
		if (tmp->type == PIPE && tmp->next->type == PIPE)
			return (parse_error(tmp->str));
		tmp = tmp->next;
	}
	return (0);
}

static void			get_type(t_lex *lexer)
{
	t_lexer		*tmp;

	tmp = lexer->start;
	while (tmp)
	{
		tmp->type = keytotype(tmp->str);
		tmp = tmp->next;
	}
}

t_parse		*msh_parseur(t_lex *lexer, char ***env)
{
	t_parse		*tree;
	t_lexer		*tmp;

	tree = NULL;
	get_type(lexer);
	if (first_check(lexer))
		return (tree);
	tmp = lexer->start;
	tree = browse_lex(tmp, env);
	return (tree);
}
