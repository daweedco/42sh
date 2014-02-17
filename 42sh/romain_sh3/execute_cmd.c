/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:29:20 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/09 20:43:40 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

void	execute_error(char *cmd)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
}

int		execute_mycmd(t_cmd **cmd)
{
	(*cmd)->cmd_arg = ft_strsplit((*cmd)->arg, ' ');
	if (ft_strcmp((*cmd)->path, "exit") == 0 && (*cmd)->id > 0)
		restore_env();
	if (ft_strcmp((*cmd)->path, "env") == 0)
	{
		execute_env((*cmd)->env);
		return (0);
	}
	else if (ft_strcmp((*cmd)->path, "setenv") == 0)
	{
		(*cmd)->env = execute_setenv((*cmd)->env, (*cmd)->cmd_arg);
		return (0);
	}
	else if (ft_strcmp((*cmd)->path, "unsetenv") == 0)
	{
		(*cmd)->env = execute_unsetenv((*cmd)->env, (*cmd)->cmd_arg);
		return (0);
	}
	else if (ft_strcmp((*cmd)->path, "cd") == 0)
	{
		*cmd = my_cd(*cmd, 0);
		return (0);
	}
	return (-1);
}

t_cmd	*execute_cmd(t_cmd *cmd)
{
	cmd->exec = 0;
	cmd->id = 1;
	if (cmd->path == NULL)
		return (cmd);
	if (execute_mycmd(&cmd) == 0)
		return (cmd);
	cmd->id = fork();
	cmd->cmd_arg = ft_strsplit(cmd->arg, ' ');
	if (cmd->fd != -1)
		dup2(cmd->fd, 1);
	if (cmd->id == 0)
		execve(cmd->path, cmd->cmd_arg, cmd->env);
	if (cmd->id > 0)
		wait(NULL);
	close(cmd->fd);
	dup2(cmd->fd_out, 1);
	cmd->fd = -1;
	return (cmd);
}
