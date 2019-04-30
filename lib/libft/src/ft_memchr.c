/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:42:20 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 18:41:56 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c2;

	if (n == 0)
		return (NULL);
	c2 = (unsigned char)c;
	str = (unsigned char*)s;
	while (*str != '\0' && n != 0)
	{
		if (*str == c2)
			return (str);
		str++;
		n--;
	}
	if (*str == c2 && c2 == '\0')
		return (str);
	return (NULL);
}
