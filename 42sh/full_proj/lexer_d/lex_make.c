/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_make.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 19:26:57 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/13 19:40:56 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

static char			lex_get_type(char *op)
{
	if (!ft_strncmp(op, "<<", 2))
		return (APPEND);
	else if (!ft_strncmp(op, ">>", 2))
		return (APPEND);
	else if (!ft_strncmp(op, "||", 2))
		return (OR);
	else if (!ft_strncmp(op, "&&", 2))
		return (AND);
	else if (*op == '<')
		return (REDIR);
	else if (*op == '>')
		return (REDIR);
	else if (*op == '|')
		return (PIPE);
	else if (*op == ';')
		return (SEP);
	return (CMD);

}

static void			add_operator(t_lx *lex, int ret, char *tolex)
{
	t_lexer		*token;

	token = new_token();
	token->str = ft_strsub(tolex, 0, ret);
	token->type = lex_get_type(token->str);
	add_token(lex, token);
}

static void			add_to_lex(char *cmd, char *tolex, t_lx *lex, int ret)
{
	t_lexer		*token;
	char		*tmp;

	if ((tolex - cmd) > 0)
	{
		token = new_token();
		tmp = ft_strsub(cmd, 0, (tolex - cmd));
		token->str = ft_strtrim(tmp);
		free(tmp);
		add_token(lex, token);
	}
	if (*tolex)
		add_operator(lex, ret, tolex);
}

static int			check_key(char *ptr)
{
	static char		*key_two[] = {">>", "<<", "&&", "||", NULL};
	static char		key_one[] = "\"\'`><|;";
	int				ret;
	int				i;

	i = 0;
	while (key_two[i])
	{
		if (!ft_strncmp(ptr, key_two[i], 2))
			return (2);
		i++;
	}
	i = 0;
	ret = 1;
	while (key_one[i])
	{
		if (key_one[i] == *ptr)
		{
			if (lex_isquote(ptr))
				ret = browse_quote(ptr);
			return (ret);
		}
		i++;
	}
	return (0);
}

void				make_lex(t_lx *lex, char *cmd)
{
	char	*tolex;
	int		ret;

	ret = 0;
	tolex = cmd;
	while (*tolex)
	{
		if ((ret = check_key(tolex)))
		{
			add_to_lex(cmd, tolex, lex, ret);
			tolex += ret;
			cmd = tolex;
		}
		else
			tolex++;
	}
	if (cmd != tolex)
		add_to_lex(cmd, tolex, lex, ret);
}
