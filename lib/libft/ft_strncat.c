/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:27:42 by jloro             #+#    #+#             */
/*   Updated: 2017/11/10 14:25:11 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int		i;
	size_t	compteur;

	compteur = 0;
	i = 0;
	while (dest[i] != '\0')
		i++;
	while (*src && compteur < n)
	{
		dest[i] = *src;
		src++;
		i++;
		compteur++;
	}
	dest[i] = '\0';
	return (dest);
}
