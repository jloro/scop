/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:13:01 by jloro             #+#    #+#             */
/*   Updated: 2019/04/11 15:01:49 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xpm.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void					clean(t_imgInfos *core)
{
	int					i;

	i = 0;
	while (i < core->nbColor)
	{
		printf("oui\n");
		free(core->colors[i]);
	}
	free(core->colors);
	i = 0;
	while (i < core->nbColor)
		free(core->ch[i]);
	free(core->ch);
}

int						findIndex(char **tab, char toFindF, char toFindS, int len)
{
	int					i;

	i = 0;
	while (i < len)
	{
		if (tab[i][0] == toFindF && tab[i][1] == toFindS)
			return i;
		i++;
	}
	return -1;
}

int						parseIMG(int fd, t_imgInfos * core)
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
			index = findIndex(core->ch, line[j], line[j + 1], core->nbColor);
			core->data[(i * core->width + ((j - 1) / 2)) * 3] = core->colors[index][0];
			core->data[(i * core->width + ((j - 1) / 2)) * 3 + 1] = core->colors[index][1];
			core->data[(i * core->width + ((j - 1) / 2)) * 3 + 2] = core->colors[index][2];
			j += 2;
		}
		free(line);
		i++;
	}
	return 1;
}

unsigned char *			parseHexaColor(char * hexa)
{
	unsigned char *	colors;
	char		tmp[3];

	if ((colors = (unsigned char *)malloc(sizeof(unsigned char) * 3)) == NULL)
		return NULL;
	hexa++;
	ft_strncpy(tmp, hexa, 2);
	colors[0] = ft_itoa_dec(tmp, 16);
	hexa += 2;
	ft_strncpy(tmp, hexa, 2);
	colors[1] = ft_itoa_dec(tmp, 16);
	hexa += 2;
	ft_strncpy(tmp, hexa, 2);
	colors[2] = ft_itoa_dec(tmp, 16);
	return colors;
}

int				parseColor(int fd, t_imgInfos *core)
{
	char			*line;
	int				i;

	i = 0;
	if ((core->colors = (unsigned char **)malloc(sizeof(unsigned char*) * core->nbColor)) == NULL)
		return 0;
	if ((core->ch = (char **)malloc(sizeof(char*) * core->nbColor)) == NULL)
		return 0;
	while (i < core->nbColor)
	{
		get_next_line(fd, &line);
		if ((core->ch[i] = (char *)malloc(sizeof(char) * core->nbChar + 1)) == NULL)
			return 0;
		ft_strncpy(core->ch[i], line + 1, core->nbChar);
		core->ch[i][core->nbChar] = '\0';
		if ((core->colors[i] = parseHexaColor(strstr(line, "c #") + 2)) == NULL)
			return 0;
		i++;
		free(line);
	}
	return 1;
}

unsigned char	*loadXPM(const char * path, int * width, int * height)
{
	int				fd;
	t_imgInfos		core;
	char			*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return NULL;
	get_next_line(fd, &line);
	free(line);
	get_next_line(fd, &line);
	sscanf(line, "\"%d %d %d %d \",", &(core.width), &(core.height), &(core.nbColor), &(core.nbChar));
	free(line);
	core.data = (unsigned char *)malloc(sizeof(unsigned char) * 3 * core.width * core.height);
	*width = core.width;
	*height = core.height;
	printf("w: %d h: %d col:%d ch: %d\n", core.width, core.height, core.nbColor, core.nbChar);
	parseColor(fd, &core);
	parseIMG(fd, &core);
	close(fd);
	//KC
	//clean(&core);
	return core.data;
}
