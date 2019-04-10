/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:01 by jloro             #+#    #+#             */
/*   Updated: 2018/01/11 16:31:11 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_itoa_dec(char *nbr, int base)
{
	int	nb;
	int	len;
	int	power;

	nb = 0;
	power = 0;
	len = ft_strlen(nbr) - 1;
	while (len >= 0)
	{
		if (nbr[len] - '0' < 10)
			nb += (nbr[len] - '0') * ft_power(base, power);
		else
			nb += (nbr[len] - 55) * ft_power(base, power);
		power++;
		len--;
	}
	return (nb);
}
