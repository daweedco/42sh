/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 21:27:22 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/09 17:08:22 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

static void	handle_stop(void)
{
	g_stop = 1;
}

void		handle_signal(int sig)
{
	if (sig == SIGINT)
		handle_stop();
}

void		catch_signal(void)
{
	int		i;

	i = 1;
	while (i < 32)
	{
		signal(i, handle_signal);
		i++;
	}
}
