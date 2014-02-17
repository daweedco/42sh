/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 19:22:03 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/05 16:42:01 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

static void		execute_pipe(t_pipe *pipe_info, t_cmd *cmd)
{
	int		pipe_fd[2];
	pid_t	id;

	pipe(pipe_fd);
	id = fork();
	if (id == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		execve(pipe_info->path1, pipe_info->cmd1, cmd->env);
		close(pipe_fd[1]);
		return ;
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		if (cmd->fd != -1)
			dup2(cmd->fd, 1);
		execve(pipe_info->path2, pipe_info->cmd2, cmd->env);
		close(pipe_fd[0]);
	}
}

static t_cmd	*get_arg(t_cmd *cmd)
{
	cmd->i++;
	cmd->arg = ft_clean(cmd->cmd[cmd->i], 0, 0);
	cmd->i++;
	while (cmd->cmd[cmd->i])
	{
		if (cmd->cmd[cmd->i][0] == ';' || cmd->cmd[cmd->i][0] == '|')
			return (cmd);
		if (cmd->cmd[cmd->i][0] == '>')
		{
			cmd->fd = open_file(cmd->cmd[cmd->i], cmd->cmd[cmd->i + 1]);
			cmd->i++;
		}
		else
		{
			cmd->arg = ft_strjoin(cmd->arg, " ");
			cmd->arg = ft_strjoin(cmd->arg, ft_clean(cmd->cmd[cmd->i], 0, 0));
		}
		cmd->i++;
	}
	return (cmd);
}

static int		is_mycmd(char *path)
{
	if (ft_strcmp(path, "exit") == 0 || ft_strcmp(path, "setenv") == 0
		|| ft_strcmp(path, "env") == 0 || ft_strcmp(path, "cd") == 0
		|| ft_strcmp(path, "unsetenv") == 0)
		return (0);
	else
		return (1);
}

t_cmd			*init_pipe(t_cmd *cmd)
{
	t_pipe	*pipe;
	pid_t	id;

	cmd->exec = 0;
	if (is_mycmd(cmd->path) == 0)
		return (cmd);
	pipe = (t_pipe *)malloc(sizeof(t_pipe));
	pipe->path1 = ft_strdup(cmd->path);
	pipe->cmd1 = ft_strsplit(cmd->arg, ' ');
	if ((cmd->path = which_path(cmd->cmd[cmd->i + 1])) == NULL
		|| execute_mycmd(&cmd) == 0)
		return (cmd);
	pipe->path2 = ft_strdup(cmd->path);
	cmd = get_arg(cmd);
	pipe->cmd2 = ft_strsplit(cmd->arg, ' ');
	id = fork();
	if (id == 0)
		execute_pipe(pipe, cmd);
	else if (id > 0)
		wait(NULL);
	dup2(cmd->fd_out, 1);
	close(cmd->fd);
	cmd->fd = -1;
	return (cmd);
}
