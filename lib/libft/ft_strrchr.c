/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:29:15 by jloro             #+#    #+#             */
/*   Updated: 2017/11/10 14:39:47 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int len;

	len = ft_strlen(s);
	while (s[len] != c && len >= 0)
		len--;
	if (len < 0)
	{
		while (*s)
			s++;
		return (0);
	}
	else
	{
		while (len > 0)
		{
			s++;
			len--;
		}
	}
	return ((char*)s);
}
