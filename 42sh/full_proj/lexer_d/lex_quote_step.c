/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_first_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 19:23:51 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/14 17:41:56 by dcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

int				get_next_quote(char **more, char *buf, char quote)
{
	char	*new;
	int		i;

	i = 0;
	if (*more == NULL)
		*more = ft_strdup(buf);
	else
	{
		new = ft_strjoin(*more, buf);
		free(*more);
		*more = new;
	}
	while ((*more)[i])
	{
		if ((*more)[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

char			*get_more(char quote)
{
	char		buf[BUFF_QUOTE + 1] = {0};
	int			ret;
	char		*more;
	char		*quote_prompt[] = {"<dquote>", "<squote>", "<bquote>"};
	char		*ptr;

	more = NULL;
	if (quote == '"')
		ptr = quote_promtp[0];
	else if (quote == '\'')
		ptr = quote_promtp[1];
	else if (quote == '`')
		ptr = quote_promtp[2];
	while (42)
	{
		write(1, ptr, 9);
		ret = read(0, buf, BUFF_QUOTE);
		buf[ret - 1] = '\0';
		if (get_next_quote(&more, buf, quote))
			break ;
	}
	return (more);
}

static char		*get_next(char *cmd, int i, char quote)
{
	char		*more;

	while (cmd[i])
	{
		if (cmd[i] == quote)
			return (NULL);
		i++;
	}
	more = get_more(quote); //a faire
	return (more);
}

static void		cat_cmd(char **cmd_ptr, char **str)
{
	char		*new;

	new = ft_strnew(ft_strlen(*cmd_ptr) + ft_strlen(*str));
	new = ft_strcat(new, *cmd_ptr);
	new = ft_strcat(new, *str);
	free(*cmd_ptr);
	*cmd_ptr = new;
	free(*str);
	*str = NULL;
}

static void		check_quote(char **cmd_ptr, char *quote)
{
	int		i;
	char	*more;
	char	*cmd;

	more = NULL;
	cmd = *cmd_ptr;
	while (*quote)
	{
		i = 0;
		while (cmd[i])
		{
			if (*quote == cmd[i] && (!cmd[i - 1] || cmd[i - 1] != '\\'))
			{
				more = get_next(cmd, (i + 1), *quote);
				break ;
			}
			i++;
		}
		if (more != NULL)
			cat_cmd(cmd_ptr, &more);
		quote++;
	}
}

void			stp_quote(char **cmd, char **env)
{
	static char		quote[] = "\"\'`";

	(void)env;
	check_quote(cmd, quote);
}
