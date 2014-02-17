/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 16:59:53 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/31 19:13:48 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_minishell.h"

static void		replace_env(char ***env, int nb, char *new)
{
	int			i;
	char		**newenv;

	i = 0;
	while ((*env)[i])
		i++;
	if ((newenv = (char **)(malloc(sizeof(char *) * (i + 1)))) == NULL)
		exit(ft_print_error("malloc"));
	i = 0;
	while ((*env)[i])
	{
		if (i == nb)
			newenv[i] = ft_strdup(new);
		else
			newenv[i] = ft_strdup((*env)[i]);
		i++;
	}
	newenv[i] = '\0';
	ft_tabfree(env);
	*env = newenv;
}

int		ft_setenv(const char *name, const char *value, int ow, char ***env)
{
	int			i;
	char		*tmp;

	i = -1;
	if ((tmp = ft_strjoinwsep(name, value, '=')) == NULL)
		return (-1);
	while ((*env)[++i])
	{
		if (msh_isenv((*env)[i], name))
		{
			if (ow == 0)
				return (0);
			replace_env(env, i, tmp);
			free(tmp);
			return (0);
		}
	}
	if ((ft_tab_realloc(env, tmp) == -1))
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}
