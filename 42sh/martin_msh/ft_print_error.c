/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 18:45:27 by mle-roy           #+#    #+#             */
/*   Updated: 2014/01/26 16:15:37 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		ft_print_error(char *error)
{
	write(2, "[error]: ", 8);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (-1);
}
