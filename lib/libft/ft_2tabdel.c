/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2tabdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:01:50 by jloro             #+#    #+#             */
/*   Updated: 2018/01/09 14:25:20 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_2tabdel(void **tab, int len)
{
	unsigned char	**tab2;
	int				i;

	i = 0;
	tab2 = (unsigned char**)tab;
	while (i < len)
	{
		free(tab2[i]);
		i++;
	}
	free(tab2);
}
