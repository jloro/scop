/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:13:01 by jloro             #+#    #+#             */
/*   Updated: 2019/04/19 16:21:11 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xpm.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int						find_index(char **tab, char to_find_f, char to_find_s,
							int len)
{
	int					i;

	i = 0;
	while (i < len)
	{
		if (tab[i][0] == to_find_f && tab[i][1] == to_find_s)
			return (i);
		i++;
	}
	return (-1);
}

int						parse_img(int fd, t_img_infos *core)
{
	int					i;
	char				*line;
	int					j;
	int					index;

	i = 0;
	while (i < core->height)
	{
		j = 1;
		get_next_line(fd, &line);
		while (j < core->width * 2)
		{
			index = find_index(core->ch, line[j], line[j + 1], core->nb_color);
			core->data[(i * core->width + ((j - 1) / 2)) * 3] =
				core->colors[index][0];
			core->data[(i * core->width + ((j - 1) / 2)) * 3 + 1] =
				core->colors[index][1];
			core->data[(i * core->width + ((j - 1) / 2)) * 3 + 2] =
				core->colors[index][2];
			j += 2;
		}
		free(line);
		i++;
	}
	return (1);
}

unsigned char			*parse_hexa_color(char *hexa)
{
	unsigned char		*colors;
	char				tmp[3];

	if ((colors = (unsigned char *)malloc(sizeof(unsigned char) * 3)) == NULL)
		return (NULL);
	hexa++;
	ft_strncpy(tmp, hexa, 2);
	colors[0] = ft_itoa_dec(tmp, 16);
	hexa += 2;
	ft_strncpy(tmp, hexa, 2);
	colors[1] = ft_itoa_dec(tmp, 16);
	hexa += 2;
	ft_strncpy(tmp, hexa, 2);
	colors[2] = ft_itoa_dec(tmp, 16);
	return (colors);
}

int						parse_color(int fd, t_img_infos *core)
{
	char				*line;
	int					i;

	i = 0;
	if ((core->colors = (unsigned char **)malloc(sizeof(unsigned char*)
					* core->nb_color)) == NULL)
		return (0);
	if ((core->ch = (char **)malloc(sizeof(char*) * core->nb_color)) == NULL)
		return (0);
	while (i < core->nb_color)
	{
		get_next_line(fd, &line);
		if ((core->ch[i] = (char *)malloc(sizeof(char) * core->nb_char + 1))
				== NULL)
			return (0);
		ft_strncpy(core->ch[i], line + 1, core->nb_char);
		core->ch[i][core->nb_char] = '\0';
		if ((core->colors[i] = parse_hexa_color(strstr(line, "c #") + 2))
				== NULL)
			return (0);
		i++;
		free(line);
	}
	return (1);
}

unsigned char			*loadxpm(const char *path, int *width, int *height)
{
	int					fd;
	t_img_infos			core;
	char				*line;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	get_next_line(fd, &line);
	free(line);
	get_next_line(fd, &line);
	sscanf(line, "\"%d %d %d %d \",", &(core.width), &(core.height),
			&(core.nb_color), &(core.nb_char));
	free(line);
	if ((core.data = (unsigned char *)malloc(sizeof(unsigned char) * 3
					* core.width * core.height)) == NULL)
		return (0);
	*width = core.width;
	*height = core.height;
	parse_color(fd, &core);
	parse_img(fd, &core);
	close(fd);
	ft_2tabdel((void**)core.colors, core.nb_color);
	ft_2tabdel((void**)core.ch, core.nb_color);
	return (core.data);
}
