/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 11:43:35 by jloro             #+#    #+#             */
/*   Updated: 2018/01/11 15:52:08 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** BASE 2-16 && NB > 0
*/

char		*ft_itoa_base(int nb, int base)
{
	int		nbbis;
	int		len;
	char	*nbr;

	len = 0;
	nbbis = nb;
	while (nbbis != 0)
	{
		nbbis /= base;
		len++;
	}
	nbr = (char*)malloc(sizeof(char) * (len + 1));
	nbr[len--] = '\0';
	while (nb != 0)
	{
		if (nb % base > 9)
			nbr[len] = nb % base + 55;
		else
			nbr[len] = nb % base + '0';
		nb /= base;
		len--;
	}
	return (nbr);
}
