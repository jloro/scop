/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:17:51 by jloro             #+#    #+#             */
/*   Updated: 2018/01/06 17:49:12 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_mot(char const *s, char c)
{
	int			i;
	int			mot;

	if (*s == '\0')
		return (0);
	mot = 0;
	i = 1;
	if (s[0] != c)
		mot++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			mot++;
		i++;
	}
	return (mot);
}

static	int		ft_strlendif(char const *str, char c)
{
	int			compteur;
	int			i;

	i = 0;
	compteur = 0;
	while (*str && *str != c)
	{
		compteur++;
		str++;
	}
	return (compteur);
}

static	void	ft_fill(char const *s, char *str, char c)
{
	int			i;

	i = 0;
	while (*s != c && *s)
	{
		str[i] = *s;
		s++;
		i++;
	}
	str[i] = '\0';
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	int			i;
	int			mot;

	if (s == NULL)
		return (NULL);
	mot = ft_mot(s, c);
	i = 0;
	tab = (char**)malloc(sizeof(char*) * (mot + 1));
	if (tab == NULL)
		return (NULL);
	while (i < mot)
	{
		while (*s == c)
			s++;
		if ((tab[i] = (char*)malloc(sizeof(char) * ft_strlendif(s, c))) == NULL)
			return (NULL);
		ft_fill(s, tab[i], c);
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
