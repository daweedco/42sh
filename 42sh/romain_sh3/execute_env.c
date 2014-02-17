/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 15:40:41 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/05 16:42:44 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

char	**execute_unsetenv(char **env, char **cmd)
{
	env = delete_var(env, cmd);
	return (env);
}

char	**execute_setenv(char **env, char **cmd)
{
	env = modify_var(env, cmd);
	return (env);
}

void	execute_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}
