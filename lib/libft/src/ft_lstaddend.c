/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:33:06 by jloro             #+#    #+#             */
/*   Updated: 2017/11/23 16:58:04 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **begin, t_list *end)
{
	t_list	*tmp;

	tmp = *begin;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = end;
}
