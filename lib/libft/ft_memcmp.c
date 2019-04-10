/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:52:55 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 12:20:25 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*str1;
	unsigned const char	*str2;
	size_t				c;

	if (n == 0)
		return (0);
	c = 1;
	str1 = s1;
	str2 = s2;
	while ((*str1 == *str2) && (c < n))
	{
		str1++;
		str2++;
		c++;
	}
	return (*str1 - *str2);
}
