/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 21:25:15 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/26 21:35:04 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_minishell.h"

void		set_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	msh_putprompt();
}

void		set_signal2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}
