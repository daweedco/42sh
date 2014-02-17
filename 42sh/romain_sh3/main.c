/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 18:58:47 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/09 18:07:41 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

int		tputchar(int c)
{
	write(3, &c, 1);
	return (1);
}

t_cmd	*init_struct(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->env = init_env();
	cmd->exec = 0;
	cmd->count = 0;
	cmd->fd = -1;
	cmd->save = ft_strdup("");
	cmd->fd_out = dup(1);
	cmd->pwd = ft_strdup("");
	cmd->old_pwd = ft_strdup("");
	return (cmd);
}

int		main(void)
{
	struct termios	term;
	t_cmd			*cmd;

	g_stop = 0;
	cmd = init_struct();
	term = init_term();
	while (42)
	{
		ft_putstr("$>");
		cmd->c = 2;
		cmd->i = 0;
		cmd->line = ft_strdup("");
		cmd = ft_select(cmd);
		ft_putchar('\n');
		cmd->cmd = ft_strsplit_space((char const *)cmd->line);
		init_cmd(cmd);
	}
	restore_env();
	return (0);
}
