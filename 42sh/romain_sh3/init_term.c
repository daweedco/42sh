/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:18:52 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/12 19:11:24 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell3.h"

void			restore_env(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	tputs(tgetstr("te", NULL), 1, tputchar);
	term.c_lflag |= ICANON;
//	term.c_lflag != ECHO;
	term.c_lflag |= ECHO;
	term.c_lflag &= ~(ISIG);
	tcsetattr(0, 0, &term);
	exit(0);
}

struct termios	init_term(void)
{
	struct termios	term;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag |= ISIG;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &term);
	tputs(tgetstr("ti", NULL), 1, tputchar);
	return (term);
}
