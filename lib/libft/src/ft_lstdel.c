/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 20:22:33 by jloro             #+#    #+#             */
/*   Updated: 2017/11/15 17:39:02 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*list2;

	list = *alst;
	while (list)
	{
		list2 = list->next;
		del(list->content, list->content_size);
		free(list);
		list = list2;
	}
	*alst = NULL;
}
