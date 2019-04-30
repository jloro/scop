/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:21:06 by jloro             #+#    #+#             */
/*   Updated: 2017/11/10 12:47:20 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (*haystack || *haystack == *needle)
	{
		while (haystack[j] == needle[i] && needle[j] != '\0')
		{
			j++;
			i++;
		}
		if (needle[i] == '\0')
			return ((char*)haystack);
		j = 0;
		i = 0;
		haystack++;
	}
	return (NULL);
}
