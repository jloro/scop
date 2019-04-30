/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:05:14 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 12:19:52 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	c;

	if (n == 0)
		return (1);
	if (s1 == NULL || s2 == NULL)
		return ((int)NULL);
	c = 0;
	if (n == 0)
		return (0);
	while ((*s1) && (*s2) && (*s1 == *s2) && (c < n))
	{
		c++;
		s1++;
		s2++;
	}
	if ((*s1 == '\0' && *s2 == '\0') || c == n)
		return (1);
	else
		return (0);
}
