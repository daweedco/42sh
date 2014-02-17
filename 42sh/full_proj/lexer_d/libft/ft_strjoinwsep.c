/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinwsep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/11 14:46:10 by mle-roy           #+#    #+#             */
/*   Updated: 2013/12/11 14:54:04 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinwsep(char const *s1, char const *s2, char c)
{
	char	*new;
	char	*tmp;
	char	*c_;

	c_ = ft_strnew(1);
	c_[0] = c;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		new = ft_strjoin(c_, s2);
		free(c_);
		return (new);
	}
	if (s2 == NULL)
	{
		new = ft_strjoin(s1, c_);
		free(c_);
		return (new);
	}
	tmp = ft_strjoin(s1, c_);
	new = ft_strjoin(tmp, s2);
	free(tmp);
	free(c_);
	return (new);
}
