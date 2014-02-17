/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 19:14:26 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/14 13:10:29 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "libft.h"

int		msh_env(char **req, char ***env)
{
	int				i;

	(void)req;
	i = 0;
	while ((*env)[i])
	{
		ft_putendl((*env)[i]);
		i++;
	}
	return (1);
}
