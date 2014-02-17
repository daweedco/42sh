/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsed_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 14:35:34 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 14:40:54 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_minishell.h"

void			parsed_print_tree(t_parse *tree)
{
	t_cmd		*cmd;
	t_inst		*inst;
	char		**arg;
	t_redir		*redir;
	t_append	*append;
	int			i;
	int			t;

	i = 1;
	t = 1;
	cmd = tree->cmd;
	while (cmd)
	{
		printf(">>>>>>>>>>>>>>>CMD[%d]\n", t);
		if (cmd->redir)
		{
			redir = cmd->redir;
			while (redir)
			{
				printf("first redir = %s\n", redir->name);
				if (redir->a_next)
					printf("append in redir = %s\n", redir->a_next->name);
				redir = redir->r_next;
			}
		}
		inst = cmd->inst;
		while (inst)
		{
			printf(">>>>INST[%d]\n", i);
			arg = inst->arg;
			while (*arg)
			{
				printf("arg=%s\n", *arg);
				arg++;
			}
			if (inst->redir)
			{
				redir = inst->redir;
				while (redir)
				{
					printf("redir=%s\n", redir->name);
					if (redir->a_next)
					{
						append = redir->a_next;
						while (append)
						{
							printf("in redir append=%s\n", append->name);
							append = append->a_next;
						}
					}
					redir = redir->r_next;
				}
			}
			if (inst->append)
			{
				append = inst->append;
				while (append)
				{
					printf("append=%s\n", append->name);
					if (append->r_next)
					{
						redir = append->r_next;
						while (redir)
						{
							printf("in append redir=%s\n", redir->name);
							redir = redir->r_next;
						}
					}
					append = append->a_next;
				}
			}
			i++;
			inst = inst->next;
		}
		i = 1;
		t++;
		cmd = cmd->next;
	}
}
