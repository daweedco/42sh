/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 17:40:51 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/07 18:39:48 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft_minishell.h"
#include "libft.h"

static int			exec_cmd_pipe(t_inst *inst, t_parse *tree)
{
	char	*tmp;
	char	**path;

	path = tree->path;
	if (check_builtin(inst->arg, tree->env) == 0)
	{
		if (check_access(*(inst->arg)))
			execve(*(inst->arg), inst->arg, *(tree->env));
		while (*path)
		{
			tmp = ft_strjoinwsep(*path, *(inst->arg), '/');
			if (check_access(tmp))
			{
				execve(tmp, inst->arg, *(tree->env));
				free(tmp);
				return (0);
			}
			free(tmp);
			path++;
		}
		access_error(*(inst->arg), tree->path);
		exit(0);
	}
	exit(0);
}

static void			pipe_inst(t_inst *inst, t_parse *tree, int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	exec_cmd_pipe(inst, tree);
}

static void			close_pipe(int infile, int outfile, t_inst *inst)
{
	if (infile != inst->in_p)
		close(infile);
	if (outfile != inst->out_p)
		close(outfile);
}

void				exec_pipe(t_inst *inst, t_parse *tree)
{
	int			pipex[2];
	pid_t		pid;
	int			infile;
	int			outfile;

	infile = inst->in_p;
	while (inst)
	{
		if (inst->next)
		{
			pipe(pipex);
			outfile = pipex[1];
		}
		else
			outfile = inst->out_p;
		if ((pid = fork()) == 0)
			pipe_inst(inst, tree, infile, outfile);
		close_pipe(infile, outfile, inst);
		infile = pipex[0];
		inst = inst->next;
	}
	waitpid(pid, NULL, WUNTRACED);
	exit(0);
}
