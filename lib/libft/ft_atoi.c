/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:50:22 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 16:20:08 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	int n;
	int nb;

	n = 1;
	nb = 0;
	if (*nptr == '\200')
		return (0);
	while ((*nptr <= ' ' || *nptr == 127) && *nptr != '\e')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			n = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9' && *nptr != '\0')
	{
		nb = nb * 10 + *nptr - 48;
		nptr++;
	}
	nb *= n;
	return (nb);
}
