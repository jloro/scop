/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:59:56 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 16:21:46 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	n;
	int		dst_size;

	n = size - ft_strlen(dst) - 1;
	i = 0;
	j = 0;
	dst_size = ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (ft_strlen(src) + size);
	while (dst[i] != '\0')
		i++;
	while (j < n && src[j] != '\0')
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (ft_strlen(src) + dst_size);
}
