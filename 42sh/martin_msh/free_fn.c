/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 16:22:02 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 16:51:23 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_minishell.h"

void			free_inst(t_inst *inst)
{
	ft_tabfree(&(inst->arg));
	if (inst->redir)
	{
		free(inst->redir->name);
		free(inst->redir);
	}
	if (inst->append)
	{
		free(inst->append->name);
		free(inst->append);
	}
	free(inst);
}

void			free_lst_append(t_append *append)
{
	t_append	*tmp;
	t_append	*keep;

	tmp = append;
	while (tmp)
	{
		free(tmp->name);
		if (tmp->r_next)
			free_lst_redir(tmp->r_next);
		keep = tmp;
		tmp = tmp->a_next;
		free(keep);
	}
}

void			free_lst_redir(t_redir *redir)
{
	t_redir		*tmp;
	t_redir		*keep;

	tmp = redir;
	while (tmp)
	{
		free(tmp->name);
		if (tmp->a_next)
			free_lst_append(tmp->a_next);
		keep = tmp;
		tmp = tmp->r_next;
		free(keep);
	}
}

void			free_lst_inst(t_inst *inst)
{
	t_inst		*tmp;
	t_inst		*keep;

	tmp = inst;
	while (tmp)
	{
		ft_tabfree(&(tmp->arg));
		if (tmp->redir)
			free_lst_redir(tmp->redir);
		if (tmp->append)
			free_lst_append(tmp->append);
		keep = tmp;
		tmp = tmp->next;
		free(keep);
	}
}

void			free_parsed(t_parse *parsed)
{
	t_cmd		*cmd;
	t_cmd		*keep;

	ft_tabfree(&(parsed->path));
	cmd = parsed->cmd;
	while (cmd)
	{
		if (cmd->inst)
			free_lst_inst(cmd->inst);
		if (cmd->redir)
			free_lst_redir(cmd->redir);
		keep = cmd;
		cmd = cmd->next;
		free(keep);
	}
	free(parsed);
}
