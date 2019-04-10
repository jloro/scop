/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:55:49 by jloro             #+#    #+#             */
/*   Updated: 2017/11/14 16:46:16 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			com;
	unsigned char	c2;

	c2 = (unsigned char)c;
	com = 0;
	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	while (com < n)
	{
		if (s2[com] == c2)
		{
			s1[com] = s2[com];
			return (dest + com + 1);
		}
		s1[com] = s2[com];
		com++;
	}
	return (NULL);
}
