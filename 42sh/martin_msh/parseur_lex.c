/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_lex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 18:48:25 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 16:12:55 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "libft.h"

void				add_cmd_tree(t_parse *tree)
{
	t_cmd		*new_cmd;
	t_cmd		*tmp;

	new_cmd = init_cmd();
	if (tree->cmd == NULL)
		tree->cmd = new_cmd;
	else
	{
		tmp = tree->cmd;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
}

void				add_inst_tree(t_parse *tree, t_lexer *lex)
{
	t_cmd		*cmd;
	t_inst		*inst;
	t_inst		*tmp;

	inst = init_inst(lex->str);
	if (tree->cmd == NULL)
		add_cmd_tree(tree);
	cmd = tree->cmd;
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->inst == NULL)
		cmd->inst = inst;
	else
	{
		tmp = cmd->inst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = inst;
		inst->prev = tmp;
	}
}

void				cat_inst_tree(t_parse *tree, t_lexer *lex)
{
	t_cmd		*cmd;
	char		*cat_cmd;
	t_inst		*inst;
	t_inst		*tmp;
	t_inst		*keep;

	cat_cmd = ft_strjoinwsep(lex->prev->str, lex->str, ' ');
	inst = init_inst(cat_cmd);
	free(cat_cmd);
	cmd = tree->cmd;
	while (cmd->next)
		cmd = cmd->next;
	tmp = cmd->inst;
	while (tmp->next)
		tmp = tmp->next;
	if (tmp->prev)
	{
		keep = tmp->prev;
		keep->next = inst;
		inst->prev = keep;
	}
	else
		cmd->inst = inst;
	free_inst(tmp);
}
