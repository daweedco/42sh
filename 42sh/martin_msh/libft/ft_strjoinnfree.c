/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/11 14:39:04 by mle-roy           #+#    #+#             */
/*   Updated: 2013/12/11 14:43:57 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinnfree(char *s1, char const *s2)
{
	char	*new;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
	{
		new = ft_strdup(s1);
		free(s1);
		return (new);
	}
	new = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	new = ft_strcat(ft_strcpy(new, s1), s2);
	free(s1);
	return (new);
}
