/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabid-on <rabid-on@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 20:19:54 by rabid-on          #+#    #+#             */
/*   Updated: 2014/02/07 18:37:12 by rabid-on         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_create_tab(char const *str)
{
	char	**tab;
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (str[i] != 0)
	{
		if (str[i] != ' ' && str[i] != '\t')
			word++;
		while (str[i] != ' ' && str[i] != 0 && str[i] != '\t')
			i++;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
	}
	tab = (char **) ft_memalloc(sizeof(char *) * word + 1);
	return (tab);
}

char		**ft_strsplit_space(char const *str)
{
	char	**tab;
	int		start;
	int		word;
	int		i;

	if (!str)
		return ((char **) ft_memalloc(sizeof(char *)));
	tab = ft_create_tab(str);
	start = 0;
	word = -1;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] != ' ' && str[i] != '\t')
			word++;
		start = i;
		while (str[i] != ' ' && str[i] != '\t' && str[i] != 0)
			i++;
		if (word >= 0)
			tab[word] = ft_strsub(str, start, i - start);
		while (str[i] == ' ' || str[i] == '\t')
			i++;
	}
	tab[word + 1] = NULL;
	return (tab);
}
