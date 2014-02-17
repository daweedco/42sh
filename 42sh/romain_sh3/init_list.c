/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 20:12:24 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/08 17:57:29 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

t_hist	*add_list(t_cmd *cmd)
{
	t_hist	*elem;

	if (cmd->line[0] == '\0')
		return (cmd->list);
	elem = (t_hist *)malloc(sizeof(t_hist));
	elem->cmd = ft_strdup(cmd->line);
	elem->next = cmd->list;
	return (elem);
}
