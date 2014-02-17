/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 15:20:19 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 15:44:26 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_minishell.h"

static void			redir_to_inst(t_inst *inst, t_redir *redir)
{
	t_redir		*tmp_redir;

	if (inst->redir == NULL)
		inst->redir = redir;
	else
	{
		tmp_redir = inst->redir;
		while (tmp_redir->r_next)
			tmp_redir = tmp_redir->r_next;
		tmp_redir->r_next = redir;
	}
}

static void			redir_to_append(t_inst *inst, t_redir *redir)
{
	t_append	*append;

	append = inst->append;
	while (append->a_next)
		append = append->a_next;
	append->r_next = redir;
}

/*
**	Voir la gestion des appends dans les redir
*/

static void			add_redir_to_first(t_cmd *cmd, t_redir *redir, t_lexer *lex)
{
	t_redir		*tmp_redir;

	(void)lex; // nonon
	if (cmd->redir == NULL)
		cmd->redir = redir;
	else
	{
		tmp_redir = cmd->redir;
		while (tmp_redir->r_next)
			tmp_redir = tmp_redir->r_next;
		tmp_redir->r_next = redir;
	}
}

void				add_redir(t_parse *tree, t_redir *redir, t_lexer *lex)
{
	t_cmd		*cmd;
	t_inst		*inst;

	cmd = tree->cmd;
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->inst == NULL)
		add_redir_to_first(cmd, redir, lex);
	else
	{
		inst = cmd->inst;
		while (inst->next)
			inst = inst->next;
		if (lex->prev->prev->prev && lex->prev->prev->prev->type == APPEND)
			redir_to_append(inst, redir);
		else
			redir_to_inst(inst, redir);
	}
}
