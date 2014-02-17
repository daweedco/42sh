/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 16:37:38 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/05 16:42:23 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

char	**delete_var(char **env, char **cmd)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char **)malloc(sizeof(char *) * ft_tablen(env) - 1);
	while (env[i])
	{
		if (ft_strncmp(cmd[1], env[i], ft_strlen(cmd[1])) != 0)
			tmp[j++] = ft_strdup(env[i++]);
		else
			i++;
	}
	tmp[j] = NULL;
	return (tmp);
}

char	**add_var(char **env, char *var)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * ft_tablen(env) + 1);
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i] = ft_strdup(var);
	i++;
	tmp[i] = NULL;
	return (tmp);
}

char	**modify_var(char **env, char **cmd)
{
	int		i;
	char	*var;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], cmd[1], ft_strlen(cmd[1])) == 0)
		{
			env[i] = ft_strjoin(cmd[1], "=");
			env[i] = ft_strjoin(env[i], cmd[2]);
			return (env);
		}
		i++;
	}
	var = ft_strjoin(cmd[1], "=");
	var = ft_strjoin(var, cmd[2]);
	env = add_var(env, var);
	return (env);
}
