/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 16:18:33 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/12 19:09:57 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

t_cmd	*prev_cmd(char *key, t_cmd *cmd)
{
	int		j;
	t_hist	*tmp;

	j = 1;
	if (!cmd->list)
		return (cmd);
	tmp = cmd->list;
	if (ft_strcmp(key, UP) == 0 && cmd->i < cmd->count)
		cmd->i++;
	else if (ft_strcmp(key, DOWN) == 0 && cmd->i > 1)
		cmd->i--;
	while (j++ < cmd->i && tmp->next != NULL)
		tmp = tmp->next;
	tputs(tgetstr("dl", NULL), 1, tputchar);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	ft_putstr("$>");
	ft_putstr(tmp->cmd);
	cmd->line = ft_strdup(tmp->cmd);
	cmd->c = ft_strlen(tmp->cmd) + 2;
	return (cmd);
}

t_cmd	*move_word(t_cmd *cmd, char *key, int i)
{
	if (cmd->line[cmd->c - 3] == ' ' || cmd->line[cmd->c - 3] == '\t')
		i = 1;
	if (ft_strcmp(key, OPTL) == 0)
	{
		while (((cmd->line[cmd->c - 3] != ' ' && cmd->line[cmd->c - 3] != '\t')
				|| i == 1) && cmd->c > 2)
		{
			i = 0;
			tputs(tgetstr("le", NULL), 1, tputchar);
			cmd->c--;
		}
	}
	else if (ft_strcmp(key, OPTR) == 0)
	{
		while (((cmd->line[cmd->c - 3] != ' ' && cmd->line[cmd->c - 3] != '\t')
				|| i == 1) && cmd->c < (int) ft_strlen(cmd->line) + 2) //j'ai touche
		{
			i = 0;
			tputs(tgetstr("nd", NULL), 1, tputchar);
			cmd->c++;
		}
	}
	return (cmd);
}

t_cmd	*move_side(char *key, t_cmd *cmd)
{
	if (ft_strcmp(key, LEFT) == 0 && cmd->c > 2)
	{
		tputs(tgetstr("le", NULL), 1, tputchar);
		cmd->c--;
	}
	else if (ft_strcmp(key, RIGHT) == 0 && cmd->c <= (int) ft_strlen(cmd->line) + 1) //ici aussi
	{
		tputs(tgetstr("nd", NULL), 1, tputchar);
		cmd->c++;
	}
	else if (ft_strcmp(key, HOME) == 0)
	{
		cmd->c = 2;
		tputs(tgetstr("cr", NULL), 1, tputchar);
		tputs(tgetstr("nd", NULL), 1, tputchar);
		tputs(tgetstr("nd", NULL), 1, tputchar);
	}
	else if (ft_strcmp(key, END) == 0)
	{
		while (cmd->c++ < (int) ft_strlen(cmd->line) + 2) //la aussi
			tputs(tgetstr("nd", NULL), 1, tputchar);
	}
	return (cmd);
}


t_cmd	*del_char(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(cmd->line));
	if (cmd->c == 2)
		return (cmd);
	while (i < cmd->c - 3)
	{
		tmp[i] = cmd->line[i];
		i++;
	}
	while (cmd->line[i])
	{
		tmp[i] = cmd->line[i + 1];
		i++;
	}
	tmp[i] = '\0';
	cmd->line = ft_strdup(tmp);
	if (cmd->c > 2)
		cmd->c--;
	tputs(tgetstr("le", NULL), 1, tputchar);
	return (cmd);
}

t_cmd	*add_char(t_cmd *cmd, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(cmd->line) + 2));
	while (i < cmd->c - 2)
	{
		tmp[i] = cmd->line[i];
		i++;
	}
	tmp[i] = c;
	while (cmd->line[i])
	{
		tmp[i + 1] = cmd->line[i];
		i++;
	}
	tmp[i + 1] = '\0';
	cmd->line = ft_strdup(tmp);
	cmd->c++;
	tputs(tgetstr("nd", NULL), 1, tputchar);
	return (cmd);
}
