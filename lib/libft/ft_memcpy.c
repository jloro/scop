/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:12:36 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 17:10:29 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*s1;
	const char	*s2;
	size_t		c;

	c = 0;
	s1 = dest;
	s2 = src;
	while (c < n)
	{
		s1[c] = s2[c];
		c++;
	}
	return (dest);
}
