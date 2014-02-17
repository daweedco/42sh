/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 14:29:57 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/14 17:16:29 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"

#include <stdio.h> //nonon

int			sh_lexer(t_lx **lex, char **cmd, char **env)
{
	int		ret;

	ret = 0;
	stp_quote(cmd, env);
//	stp_star(cmd, env);
//	stp_tilde(cmd, env);
//	stp_dollar(cmd, env);
	*lex = init_lex();
	make_lex(*lex, *cmd);
//	if (ret = check_rules(lex))
//		free_lex(lex);
	free(*cmd); //chaine envoye dedans deja malloc ?
	cmd = NULL;
	return (ret);
}
