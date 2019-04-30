/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:54:11 by jloro             #+#    #+#             */
/*   Updated: 2017/11/10 15:00:36 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	compteur;
	int		j;

	compteur = 0;
	j = 0;
	i = 0;
	while ((*haystack || *haystack == *needle) && compteur <= len)
	{
		while (haystack[j] == needle[i] && needle[j] != '\0' && compteur < len)
		{
			compteur++;
			j++;
			i++;
		}
		if (needle[i] == '\0')
			return ((char*)haystack);
		compteur -= j;
		j = 0;
		i = 0;
		compteur++;
		haystack++;
	}
	return (NULL);
}
