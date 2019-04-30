/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 12:29:29 by jloro             #+#    #+#             */
/*   Updated: 2019/04/30 12:03:52 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int					readfd(const int fd, char **buf)
{
	char			*tmp;
	int				ret;
	char			*buftmp;

	tmp = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	while ((ret = read(fd, tmp, BUFF_SIZE)) != 0 && ret != -1)
	{
		tmp[ret] = '\0';
		if ((int)ft_strlen(tmp) != ret)
			return (-1);
		if ((buftmp = ft_strjoin(*buf, tmp)) == NULL)
			return (-1);
		free(*buf);
		*buf = ft_strdup(buftmp);
		free(buftmp);
	}
	free(tmp);
	return (ret);
}

t_list				*whichlst(t_list **begin_list, int fd)
{
	t_list			*tmp;
	t_list			*new;

	tmp = *begin_list;
	while (tmp != NULL && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		new = ft_lstnew("", 1);
		new->fd = fd;
		ft_lstaddend(begin_list, new);
		return (new);
	}
	else
		return (tmp);
}

t_list				*get_next_line2(t_list **first_lst,
						const int fd, char **line)
{
	int				ret;
	t_list			*lst;

	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (NULL);
	if (!*first_lst)
	{
		if ((*first_lst = ft_lstnew("", 1)) == NULL)
			return (NULL);
		(*first_lst)->fd = fd;
	}
	lst = whichlst(first_lst, fd);
	if ((ret = readfd(fd, (char**)&lst->content)) == -1)
		return (NULL);
	return (lst);
}

char				*ft_avance(char *buf)
{
	int				len;
	char			*new;
	int				i;
	int				j;

	j = 0;
	i = 0;
	len = ft_strlen(buf) - ft_indice_c(buf, '\n') + 1;
	if ((new = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	while (buf[i] != '\n' && buf[i] != '\0')
		i++;
	i++;
	while (buf[i] != '\0')
		new[j++] = buf[i++];
	new[j] = '\0';
	free(buf);
	return (new);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*first_lst;
	t_list			*lst;

	if ((lst = get_next_line2(&first_lst, fd, line)) == NULL)
		return (-1);
	if (ft_indice_c(lst->content, '\n') != -1)
	{
		if ((*line = ft_strsub(lst->content, 0,
					ft_indice_c(lst->content, '\n'))) == NULL)
			return (-1);
		if ((lst->content = ft_avance(lst->content)) == NULL)
			return (-1);
		return (1);
	}
	else if (ft_strcmp((char*)lst->content, "\0") != 0)
	{
		if ((*line = ft_strdup(lst->content)) == NULL)
			return (-1);
		free(lst->content);
		if ((lst->content = ft_strdup("")) == NULL)
			return (-1);
		return (1);
	}
	return (0);
}
