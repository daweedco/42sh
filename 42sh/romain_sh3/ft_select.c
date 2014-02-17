/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 21:26:07 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/09 21:17:28 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

t_cmd	*put_cmd(t_cmd *cmd, char *key)
{
	int		i;

	i = 0;
	if ((key[0] > 31 && key[0] < 127))
		cmd = add_char(cmd, key[0]);
	else if (ft_strcmp(key, DEL) == 0 || ft_strcmp(key, DEL2) == 0)
		cmd = del_char(cmd);
	tputs(tgetstr("dl", NULL), 1, tputchar);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	ft_putstr("$>");
	ft_putstr(cmd->line);
	tputs(tgetstr("cr", NULL), 1, tputchar);
	while (i++ < cmd->c)
		tputs(tgetstr("nd", NULL), 1, tputchar);
	return (cmd);
}

t_cmd	*ft_select_copy(t_cmd *cmd, char *key)
{
	if (ft_strcmp(key, OPTC) == 0)
		cmd->save = ft_strdup(cmd->line);
	else if (ft_strcmp(key, OPTV) == 0)
	{
		ft_putstr(cmd->save);
		cmd->line = ft_strjoin(cmd->line, cmd->save);
		cmd->c += ft_strlen(cmd->save);
	}
	else if (ft_strcmp(key, OPTX) == 0)
	{
		cmd->save = ft_strdup(cmd->line);
		cmd->line = ft_strdup("");
		cmd->c = 2;
		cmd = put_cmd(cmd, key);
	}
	return (cmd);
}

t_cmd	*ft_select_key(t_cmd *cmd, char *key)
{
	if ((key[0] > 31 && key[0] < 127) || ft_strcmp(key, DEL) == 0
			|| ft_strcmp(key, DEL2) == 0)
		cmd = put_cmd(cmd, key);
	else if (ft_strcmp(key, RIGHT) == 0 || ft_strcmp(key, LEFT) == 0
			|| ft_strcmp(key, HOME) == 0 || ft_strcmp(key, END) == 0)
		cmd = move_side(key, cmd);
	else if (ft_strcmp(key, UP) == 0 || ft_strcmp(key, DOWN) == 0)
		cmd = prev_cmd(key, cmd);
	else if (ft_strcmp(key, OPTL) == 0 || ft_strcmp(key, OPTR) == 0)
		move_word(cmd, key, 0);
	else
		cmd = ft_select_copy(cmd, key);
	return (cmd);
}

t_cmd	*ft_select(t_cmd *cmd)
{
	char	key[9];

	while (42)
	{
		ft_bzero(key, 9);
		read(0, key, 8);
		catch_signal();
		if (g_stop == 1)
		{
			g_stop = 0;
			cmd->line = ft_strdup("");
			cmd->c = 2;
			return (cmd);
		}
		else if (ft_strcmp(key, CTRLD) == 0)
			restore_env();
		else if (ft_strcmp(key, RETURN) == 0)
		{
			cmd->list = add_list(cmd);
			cmd->count++;
			return (cmd);
		}
		else
			cmd = ft_select_key(cmd, key);
	}
}
