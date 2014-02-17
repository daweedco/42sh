/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 20:04:16 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/14 13:10:44 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "libft.h"

int		msh_exit(char **req, char ***env)
{
	int		val;

	(void)env;
	val = 0;
	if (req[1] && req[2] && req[2] != '\0')
	{
		write(2, "exit: too many arguments\n", 25);
		return (0);
	}
	val = ft_atoi(req[1]);
	exit(val);
}
