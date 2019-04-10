/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:48:02 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 13:18:36 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_negative(int *n, int *nb)
{
	if (*n < 0)
	{
		*n *= -1;
		*nb = 0;
	}
	if (*n == -2147483648)
		*nb = 2;
}

int			ft_compte2(int n)
{
	int		c;

	c = 2;
	while (n >= 10 || n < 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		c;
	int		neg;

	neg = 1;
	c = ft_compte2(n);
	ft_negative(&n, &neg);
	str = (char*)malloc(sizeof(char) * c);
	if (str == NULL)
		return (NULL);
	str[--c] = '\0';
	c--;
	while (c >= 0)
	{
		str[c] = (n % 10) + '0';
		c--;
		n /= 10;
	}
	if (neg == 0)
		str[0] = '-';
	if (neg == 2)
		str = ft_strcpy(str, "-2147483648");
	return (str);
}
