/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_append.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 15:33:33 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 15:42:55 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_minishell.h"

static void		append_to_inst(t_inst *inst, t_append *append)
{
	t_append		*tmp_append;

	if (inst->append == NULL)
		inst->append = append;
	else
	{
		tmp_append = inst->append;
		while (tmp_append->a_next)
			tmp_append = tmp_append->a_next;
		tmp_append->a_next = append;
	}
}

static void		append_to_redir(t_inst *inst, t_append *append)
{
	t_redir		*redir;

	redir = inst->redir;
	while (redir->r_next)
		redir = redir->r_next;
	redir->a_next = append;
}

static void		add_append_to_first(t_cmd *cmd, t_append *append, t_lexer *lex)
{
//	t_append		*tmp_append;
	t_redir			*redir;

//	if (cmd->redir == NULL)
//		cmd->redir = redir;
//	else
//	{
	(void)lex; //nonon
	redir = cmd->redir;
	while (redir->r_next)
		redir = redir->r_next;
	redir->a_next = append;
//	}
}

void			add_append(t_parse *tree, t_append *append, t_lexer *lex)
{
	t_cmd		*cmd;
	t_inst		*inst;

	cmd = tree->cmd;
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->inst == NULL)
		add_append_to_first(cmd, append, lex);
	inst = cmd->inst;
	while (inst->next)
		inst = inst->next;
	if (lex->prev->prev->prev && lex->prev->prev->prev->type == REDIR)
		append_to_redir(inst, append);
	else
		append_to_inst(inst, append);
}
