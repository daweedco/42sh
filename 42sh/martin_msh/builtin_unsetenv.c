/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 19:29:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/31 14:07:54 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_minishell.h"

void	msh_remove_env(char ***env, int nb)
{
	int			i;
	int			t;
	int			j;
	char		**newenv;

	i = 0;
	t = 0;
	j = 0;
	while ((*env)[i])
		i++;
	if ((newenv = (char **)(malloc(sizeof(char *) * i))) == NULL)
		exit(ft_print_error("malloc"));
	while (j < i && t < i)
	{
		if (j == nb)
			j++;
		else
			newenv[t++] = ft_strdup((*env)[j++]);
	}
	newenv[t] = '\0';
	ft_tabfree(env);
	*env = newenv;
}

int		msh_unsetenv(char **req, char ***env)
{
	int		i;

	i = 0;
	req++;
	if (*req == NULL)
		return (0);
	while ((*env)[i])
	{
		if (msh_isenv((*env)[i], *req))
		{
			msh_remove_env(env, i);
			break ;
		}
		i++;
	}
	return (0);
}
