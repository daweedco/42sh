/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 18:16:16 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/13 14:24:39 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "libft.h"

static int		msh_do_builtin(char **req, t_builtin builtin, char ***env)
{
	builtin.fn(req, env);
	return (1);
}

int				check_builtin(char **arg, char ***env)
{
	int					i;
	static t_builtin	g_builtin[] = 	{	{"exit", &msh_exit},
											{"cd", &msh_cd},
											{"env", &msh_env},
											{"setenv", &msh_setenv},
											{"unsetenv", &msh_unsetenv},
											{"echo", &msh_echo}
										};

	i = 0;
	while (i < NB_BUILTIN)
	{
		if (ft_strcmp(g_builtin[i].name, *arg) == 0)
		{
			msh_do_builtin(arg, g_builtin[i], env);
			return (1);
		}
		i++;
	}
	return (0);
}

int				check_builtin_before(t_parse *parsed)
{
	t_cmd		*cmd;
	t_inst		*inst;

	cmd = parsed->cmd;
	if (cmd->next == NULL && cmd->redir == NULL)
	{
		inst = cmd->inst;
		if (inst->next == NULL && inst->redir == NULL && inst->append == NULL)
			return (check_builtin(inst->arg, parsed->env));
	}
	return (0);
}
