/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_second_step.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/14 16:03:07 by mle-roy           #+#    #+#             */
/*   Updated: 2014/02/14 20:15:20 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

typedef struct s_star		t_star;
typedef struct s_lst_star	t_lst_star;

struct		s_star
{
	char		*add;
	t_star		*next;
};

struct		s_lst_star
{
	t_star		*first;
	t_star		*last;
};

char	 *st_get_word(char *cmd, int start)
{
	char	 *word;
	int	 end;

	end = start;
	while (cmd[start] && !ft_isspace(cmd[start]))
		start--;
	while (cmd[end] && !ft_isspace(cmd[end]))
		end++;
	word = ft_strsub(cmd, start, end - start);
	return (word);
}


char	*find_path(char *word, int pos)
{
	int		last_pos;
	int		i;
	char	*path;

	i = 0;
	last_pos = 0;
	while (word[i] && i < pos)
	{
		if (word[i] == '/')
			last_pos = i;
		i++;
	}
	if (last_pos > 0)
		path = ft_strsub(word, 0, last_pos);
	else
		path = NULL;
	return (path);
}

char	 *st_get_path(char *word, int i)
{
	char	*path;
	char	*ptr;

	if (((ptr = ft_strchr(word, '/')) == NULL) || ptr > i)
	{
		path = ft_strnew(1);
		path[0] = '.';
	}
	else
		path = find_path(word, i);
	return (path);
}


t_lst_star		*init_lst_star(void)
{
	t_lst_star	*new;

	if ((new = (t_lst_star *)malloc(sizeof(*new))) == NULL)
		ft_exit(PROG, 1);
	new->first = NULL;
	new->last = NULL;
	return (new);
}

void			st_add_to_lst(t_lst_star *starz, char *str)
{
	t_star		*new;

	if ((new = (t_star *)malloc(sizeof(*new))) == NULL)
		ft_exit(PROG, 1);
	new->add = ft_strdup(str);
	new->next = NULL;
	if (starz->first == NULL)
	{
		startz->first = new;
		startz->last = new;
	}
	else
	{
		starz->last->next = new;
		starz->last = new;
	}
}

int				st_match_star(char *name, char *word)
{
	int		i;
	int		j;

	if (word[0] == '*' && word[1] == '\0')
		return (1);
	i = 0;
	while (name[i])
	{
		j = 0;
		while (name[i + j] == word[j] && word[j] != '*' && word[j] != 0)
			j++;
		if (word[j] == 0 && name[i + j] == 0)
			return (1);
		if (word[j] == '*')
			return (st_match_star(name + i + j, word + j + 1));
		i++;
	}
	return (0);
}

char			*get_tmp_word(char *word, int start)
{
	int		end;
	char	*tmp_word;

	end = start;
	while (word[start] && word[start] != '/')
		start--;
	while (word[end] && word[end] != '/')
		end++;
	tmp_word = ft_strsub(word, start, (start - end));
	return (tmp_word);
}

t_lst_star		*st_find_star(char *path, char *word, int i)
{
	DIR				*dir;
	struct dirent	*diren;
	t_lst_star		*starz;
	char			*tmp_word;

	starz = init_lst_star();
	dir = opendir(path);
	if (!ft_strcmp(path, "."))
		tmp_word = ft_strdup(word);
	else
		tmp_word = get_tmp_word(word, i);
	while (diren = readdir(dir))
	{
		if (st_match_star(diren->d_name, word))
			st_add_to_lst(starz, diren->d_name);
	}
	free(tmp_word);
}

t_lst_star		*get_star(char *cmd, int i)
{
	char			*word;
	char			*path;
	t_lst_star		*new;

	word = st_get_word(cmd, i);
	path = st_get_path(word, i);
	new = st_find_star(path, word, i);
	free(word);
	if (path)
		free(path);
	return (new);
}

int				star_len(t_star *ptr)
{
	int		len;
	int		space;
	t_star	*node;

	node = ptr;
	len = 0;
	space = 0;
	while (node)
	{
		len += ft_strlen(node->add);
		space++;
		node = node->next;
	}
	len += space;
	return (len);
}

void			add_star_simple(t_lst_star *starz, char **cmd, int i)
{
	int		len;
	char	*new;

	len = star_len(starz->first);
	new = ft_strnew(ft_strlen(*cmd) + len);
}

void			add_star(t_lst_star *starz, char **cmd, int i)
{
	char		*word;
	char		*ptr;

	word = st_get_word(*cmd, i);
	if ((ptr = ft_strchr(word, '/')) == NULL)
		add_star_simple(starz, cmd, i);
	else
		add_star_indir(starz, word, cmd, i);
	free(word);
}

/*
** bon j'ai pas fini add_star, mais normalement il devrait etre possible
** de lire la chaine t_lst_star
*/

void			stp_star(char **cmd_ptr, char **env)
{
	char			*cmd;
	t_lst_star		*star_list;
	int				i;

	(void)env;
	i = -1;
	cmd = *cmd_ptr;
	while (cmd[++i])
	{
		if (cmd[i] == '*')
		{
			star_list = get_star(*cmd, i);
//			add_star(star_list, &cmd, i);
			i = -1;
		}
	}
}
