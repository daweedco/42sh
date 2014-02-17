/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 12:11:17 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/26 17:40:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_minishell.h"

static void		trim_ncheck(t_lexer *lex)
{
	t_lexer		*tmp;
	t_lexer		*del;
	char		*trim;

	tmp = lex;
	while (tmp)
	{
		trim = ft_strtrim(tmp->str);
		free(tmp->str);
		tmp->str = trim;
		if (tmp->str == NULL || *(tmp->str) == '\0')
		{
			del = tmp;
			del->prev->next = del->next;
			del->next->prev = del->prev;
			tmp = del->next;
			free_node(del);
		}
		else
			tmp = tmp->next;
	}
}

static int		check_key(char *ptr)
{
	int		i;
	int		ret;
	char	*keywrd[] = {"\"", "\'", ">>", "<<", ">", "<", "|", ";", NULL};

	ret = 0;
	i = 0;
	while (keywrd[i])
	{
		if (ft_strncmp(ptr, keywrd[i], (ret = ft_strlen(keywrd[i]))) == 0)
		{
			if (*ptr == '\"' || *ptr == '\'')
				ret = browse_quote(ptr);
			if (*(--ptr) == '\\')
				ret = 0;
			return (ret);
		}
		i++;
	}
	return (0);
}

static void		add_separator(t_lex *lex, int ret, char *tolex)
{
	t_lexer		*tmp;

	tmp = new_node();
	if (lex->start == NULL)
	{
		lex->start = tmp;
		lex->last = tmp;
	}
	else
	{
		tmp->prev = lex->last;
		lex->last->next = tmp;
		lex->last = tmp;
	}
	if (*tolex == '\'' || *tolex == '\"')
		tolex++;
	lex->last->str = ft_strsub(tolex, 0, ret);
}

static void		add_to_lex(char *orig, char *tolex, t_lex *lex, int ret)
{
	t_lexer		*tmp;

	if ((tolex - orig) > 0)
	{
		if (lex->start == NULL)
		{
			lex->start = new_node();
			lex->last = lex->start;
			lex->start->str = ft_strsub(orig, 0, (tolex - orig));
		}
		else
		{
			tmp = new_node();
			tmp->prev = lex->last;
			lex->last->next = tmp;
			lex->last = tmp;
			lex->last->str = ft_strsub(orig, 0, (tolex - orig));
		}
	}
	if (*tolex)
		add_separator(lex, ret, tolex);
}

t_lex			*msh_lexer(char *orig)
{
	t_lex		*new;
	int			ret;
	char		*tolex;

	ret = 0;
	new = init_lex();
	tolex = orig;
	while (*tolex)
	{
		if ((ret = check_key(tolex)))
		{
			add_to_lex(orig, tolex, new, ret);
			if (*tolex == '\"' || *tolex == '\'')
				ret += 2;
			tolex = tolex + ret;
			orig = tolex;
		}
		else
			tolex++;
	}
	if (orig != tolex)
		add_to_lex(orig, tolex, new, ret);
	trim_ncheck(new->start);
	return (new);
}
