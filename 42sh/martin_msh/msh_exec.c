/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 18:23:08 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/05 20:06:01 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ft_minishell.h"
#include "libft.h"

static int		msh_do_command(char *path, char **req, char **env)
{
	pid_t		pid;

	if ((pid = fork()) == 0)
	{
		if (execve(path, req, env) == -1)
			exit(ft_print_error("execve"));
	}
	else
		waitpid(pid, NULL, WUNTRACED);
	return (1);
}

static int		exec_cmd(t_inst *inst, t_parse *tree)
{
	char	*tmp;
	char	**path;

	path = tree->path;
	if (check_builtin(inst->arg, tree->env) == 0)
	{
		if (check_access(*(inst->arg)))
			return (msh_do_command(*(inst->arg), inst->arg, *(tree->env)));
		while (*path)
		{
			tmp = ft_strjoinwsep(*path, *(inst->arg), '/');
			if (check_access(tmp))
			{
				msh_do_command(tmp, inst->arg, *(tree->env));
				free(tmp);
				return (0);
			}
			free(tmp);
			path++;
		}
		return (access_error(*(inst->arg), tree->path));
	}
	return (0);
}

static void		exec_inst(t_cmd *cmd, t_parse *tree)
{
	t_inst		*inst;
	pid_t		pid;

	inst = cmd->inst;
	if (inst->next == NULL)
		exec_cmd(inst, tree);
	else
	{
		if ((pid = fork()) == 0)
			exec_pipe(inst, tree);
		else
			wait(NULL);
	}
}

int				msh_exec(t_parse *tree)
{
	t_cmd		*cmd;

	cmd = tree->cmd;
	while (cmd)
	{
//		if (cmd->redir)
//			exec_first_redir(cmd, parsed);
//		else
		exec_inst(cmd, tree);
		cmd = cmd->next;
	}
	return (0);
}
