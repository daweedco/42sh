/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 19:22:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/11 19:25:12 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_minishell.h"

static int				setenv_ow(char c)
{
	if (c == '0')
		return (0);
	else
		return (1);
}

static int				treat_envmod(char **req, t_setenv *new)
{
	char			*p;

	if (req[0][0] == '-')
	{
		new->ow = setenv_ow(req[0][1]);
		req++;
		if (*req == NULL)
			return (0);
	}
	if ((p = ft_strchr(*req, '=')) != NULL)
	{
		new->name = ft_strndup(*req, (p - *req));
		new->value = ft_strdup(p + 1);
	}
	else
	{
		new->name = ft_strdup(*req);
		req++;
		if (*req)
			new->value = ft_strdup(*req);
	}
	return (1);
}

static t_setenv			*init_tsetenv(void)
{
	t_setenv		*new;

	if ((new = (t_setenv *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->ow = 1;
	new->name = NULL;
	new->value = NULL;
	return (new);
}

static void				free_tsetenv(t_setenv *new)
{
	free(new->name);
	if (new->value)
		free(new->value);
	free(new);
}

int						msh_setenv(char **req, char ***env)
{
	t_setenv	*new;
	char		**env_mod;

	env_mod = req;
	env_mod++;
	if (*env_mod == NULL)
		return (1);
	new = init_tsetenv();
	if (treat_envmod(env_mod, new))
	{
		if (ft_setenv(new->name, new->value, new->ow, env) == -1)
		{
			free_tsetenv(new);
			return (ft_print_error("ft_setenv"));
		}
	}
	free_tsetenv(new);
	return (1);
}
