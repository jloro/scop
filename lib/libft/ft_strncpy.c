/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:30:31 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 10:58:09 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	int		i;
	size_t	compteur;

	compteur = 0;
	i = 0;
	while (src[i] != '\0' && compteur < len)
	{
		dest[i] = src[i];
		i++;
		compteur++;
	}
	if (len <= ft_strlen(src))
		return (dest);
	while (compteur < len)
	{
		dest[i] = '\0';
		i++;
		compteur++;
	}
	return (dest);
}
