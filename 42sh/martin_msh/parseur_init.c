/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 14:40:25 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/07 17:53:14 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_minishell.h"
#include "libft.h"

t_redir		*init_redir(char *name, char *type)
{
	t_redir		*new;

	if ((new = (t_redir *)malloc(sizeof(*new))) == NULL)
		exit(ft_print_error("malloc"));
	new->name = ft_strdup(name);
	get_type_redir(new, type);
	new->r_next = NULL;
	new->a_next = NULL;
	return (new);
}

t_append	*init_append(char *name, char *type)
{
	t_append	*new;

	if ((new = (t_append *)malloc(sizeof(*new))) == NULL)
		exit(ft_print_error("malloc"));
	new->name = ft_strdup(name);
	get_type_append(new, type);
	new->r_next = NULL;
	new->a_next = NULL;
	return (new);
}

t_cmd		*init_cmd(void)
{
	t_cmd		*new;

	if ((new = (t_cmd *)malloc(sizeof(*new))) == NULL)
		exit(ft_print_error("malloc"));
	new->redir = NULL;
	new->inst = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_inst		*init_inst(char *str)
{
	t_inst		*new;

	if ((new = (t_inst *)malloc(sizeof(*new))) == NULL)
		exit(ft_print_error("malloc"));
	new->arg = ft_strsplitspace(str);
	new->in_p = 0;
	new->out_p = 1;
	new->redir = NULL;
	new->append = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_parse		*init_parse(char ***env)
{
	t_parse		*new;
	char		*tmp;

	if ((new = (t_parse *)malloc(sizeof(*new))) == NULL)
		exit(ft_print_error("malloc"));
	new->env = env;
	tmp = msh_get_env("PATH=", *env);
	new->path = ft_strsplit(tmp, ':');
	free(tmp);
	new->cmd = NULL;
	return (new);
}
