/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_fn1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 18:38:35 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/03 14:43:25 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_minishell.h"
#include "libft.h"

void		get_type_append(t_append *append, char *type)
{
	if (ft_strncmp(type, ">>", 2))
	{
		append->right = 1;
		append->left = 0;
	}
	else if (ft_strncmp(type, "<<", 1))
	{
		append->right = 0;
		append->left = 1;
	}
}

void		get_type_redir(t_redir *redir, char *type)
{
	if (ft_strncmp(type, ">", 1))
	{
		redir->right = 1;
		redir->left = 0;
	}
	else if (ft_strncmp(type, "<", 1))
	{
		redir->right = 0;
		redir->left = 1;
	}
}

int			parse_error(char *str)
{
	write(2, "Parse error near : \'", 20);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	return (1);
}

char		keytotype(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (APPEND);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<", 1) == 0)
		return (REDIR);
	if (ft_strncmp(str, ">", 1) == 0)
		return (REDIR);
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(str, ";", 1) == 0)
		return (S_C);
	return (COMMAND);
}
