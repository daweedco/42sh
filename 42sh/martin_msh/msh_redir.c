/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 22:10:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/01 20:35:07 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "ft_minishell.h"
/*
int				check_redir_append(t_lexer *tmp)
{
	int			check;
	int			process;

	check = 0;
	process = 1;
	while (tmp)
	{
		if (tmp->type == S_C)
			process++;
		if (tmp->type == REDIR || tmp->type == APPEND)
		{
			if (tmp->next == NULL)
				return (1);
			if (tmp->next->next && tmp->next->next->type == PIPE)
				return (1);
			if (tmp->type == APPEND || (tmp->next && tmp->next->type > 1))
				return (1);
			check++;
		}
		if (check > process)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void			exec_redir(t_parse *parsed, char **path, char ***env)
{
	pid_t		pid;
	int			fd;

	if ((pid = fork()) == 0)
	{
		if (parsed->redir->right == 1)
		{
			fd = open(parsed->redir->name, O_CREAT | O_WRONLY | O_TRUNC, 950);
			dup2(fd, 1);
			close(fd);
			pipe_command(parsed->arg, path, env);
		}
		else if (parsed->redir->left == 1)
		{
			fd = open(parsed->redir->name, O_RDWR | O_CREAT, 950);
			dup2(fd, 0);
			close(fd);
			pipe_command(parsed->arg, path, env);
		}
	}
	else
		wait(NULL);
}

void			pipe_redir(t_pipe *pipex, char **arg, char **path, char ***env)
{
	int			fd;

	if (pipex->redir->right == 1)
	{
		fd = open(pipex->redir->name, O_RDWR | O_CREAT | O_TRUNC, 950);
		dup2(fd, 1);
		close(fd);
		pipe_command(arg, path, env);
	}
	else if (pipex->redir->left == 1)
	{
		fd = open(pipex->redir->name, O_RDWR | O_CREAT, 950);
		dup2(fd, 0);
		close(fd);
		pipe_command(arg, path, env);
	}
}
*/
