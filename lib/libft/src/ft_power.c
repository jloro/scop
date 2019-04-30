/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:08:31 by jloro             #+#    #+#             */
/*   Updated: 2018/01/11 16:13:06 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int nb, int power)
{
	int	n;

	n = nb;
	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else if (power >= 1)
	{
		power--;
		nb = ft_power(nb, power);
		nb = n * nb;
		return (nb);
	}
	else
		return (nb);
}
