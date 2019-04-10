/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:22:36 by jloro             #+#    #+#             */
/*   Updated: 2017/12/01 14:47:03 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_test(const char *s1, char *str, int *i)
{
	while (*s1)
	{
		str[*i] = *s1;
		*i += 1;
		s1++;
	}
	return (str);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*str;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
	if (str == NULL)
		return (NULL);
	str = ft_test(s1, str, &i);
	while (*s2)
	{
		str[i] = *s2;
		i++;
		s2++;
	}
	str[i] = '\0';
	return (str);
}
