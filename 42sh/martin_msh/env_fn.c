/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/28 18:49:08 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/29 12:52:50 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_minishell.h"

int				msh_isenv(const char *env, const char *tofind)
{
	int		len;

	len = 0;
	if (ft_strncmp(env, tofind, len = ft_strlen(tofind)) == 0)
	{
		if (env[len] == '=' || (env[len + 1] && env[len + 1] == '='))
			return (1);
		else
			return (0);
	}
	return (0);
}

char			*msh_get_env(char *var, char **env)
{
	char			**tmp;
	char			*value;
	int				len;

	value = NULL;
	tmp = env;
	while (*tmp)
	{
		if ((ft_strnequ(*tmp, var, (len = ft_strlen(var))) == 1))
		{
			value = ft_strdup((*tmp) + len);
			return (value);
		}
		tmp++;
	}
	return (value);
}
