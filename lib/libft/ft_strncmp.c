/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:45:30 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 13:47:09 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	compteur;

	compteur = 1;
	if (n == 0)
		return (0);
	while ((*s1 == *s2) && (*s1 != '\0' || *s2 != '\0') && (compteur < n))
	{
		s1++;
		s2++;
		compteur++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
