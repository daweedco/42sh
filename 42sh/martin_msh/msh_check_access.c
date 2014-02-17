/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_check_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 16:27:29 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/26 17:44:27 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int				access_error(char *name, char **path)
{
	char	*tmp;

	if (access(name, F_OK) == 0 && access(name, X_OK) != 0)
	{
		write(2, name, ft_strlen(name));
		write(2, ": you don't have the rights to execute\n", 37);
		return (0);
	}
	while (*path)
	{
		tmp = ft_strjoinwsep(*path, name, '/');
		if (access(tmp, F_OK) == 0 && access(tmp, X_OK) != 0)
		{
			write(2, name, ft_strlen(name));
			write(2, ": you don't have the rights to execute\n", 37);
			free(tmp);
			return (0);
		}
		free(tmp);
		path++;
	}
	write(2, name, ft_strlen(name));
	write(2, ": command not found\n", 20);
	return (0);
}

int				check_access(char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}
