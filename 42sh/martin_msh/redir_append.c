/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:13:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 15:36:08 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "ft_minishell.h"
#include "libft.h"

#include <stdio.h> // non non

static void			redir_is_first(t_parse *tree, t_redir *redir)
{
	t_cmd		*cmd;

	if (tree->cmd == NULL)
		add_cmd_tree(tree);
	cmd = tree->cmd;
	while (cmd->next)
		cmd = cmd->next;
	cmd->redir = redir;
}

void				add_redir_append(t_parse *tree, t_lexer *lex)
{
	t_redir		*new_redir;
	t_append	*new_append;

	if (lex->prev && (lex->prev->type == REDIR))
	{
		new_redir = init_redir(lex->str, lex->prev->str);
		if (lex->prev->prev == NULL || lex->prev->prev->type == S_C)
			redir_is_first(tree, new_redir);
		else
			add_redir(tree, new_redir, lex);
	}
	else if (lex->prev && (lex->prev->type == APPEND))
	{
		new_append = init_append(lex->str, lex->prev->str);
		add_append(tree, new_append, lex);
	}
}
