/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:04:36 by jloro             #+#    #+#             */
/*   Updated: 2019/04/30 14:16:19 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libmat.h"
#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int					add_vertice(char *line, t_parse *info)
{
	GLfloat			*tmp;
	unsigned int	i;

	i = -1;
	info->nb_vertices++;
	if ((tmp = (GLfloat*)malloc(sizeof(GLfloat) * info->nb_vertices * 6))
			== NULL)
		return (0);
	while (++i < (info->nb_vertices - 1) * 6)
		tmp[i] = info->vertices[i];
	free(info->vertices);
	if (!sscanf(line, "v %f %f %f", &tmp[info->nb_vertices * 6 - 6],
				&tmp[info->nb_vertices * 6 - 5],
				&tmp[info->nb_vertices * 6 - 4]))
		return (0);
	tmp[info->nb_vertices * 6 - 3] = -1;
	tmp[info->nb_vertices * 6 - 2] = -1;
	tmp[info->nb_vertices * 6 - 1] = -1;
	calc_max_min(info, tmp);
	info->vertices = tmp;
	return (1);
}

int					add_face(char *line, t_parse *info, int double_face,
						int slash)
{
	GLuint			*tmp;
	unsigned int	i;
	int				select[2];

	i = -1;
	info->nb_face++;
	if ((tmp = (GLuint*)malloc(sizeof(GLuint) * info->nb_face * 3)) == NULL)
		return (0);
	while (++i < (info->nb_face - 1) * 3)
		tmp[i] = info->faces[i];
	free(info->faces);
	select[0] = double_face;
	select[1] = slash;
	add_face_if(select, line, info, tmp);
	tmp[info->nb_face * 3 - 3]--;
	tmp[info->nb_face * 3 - 2]--;
	tmp[info->nb_face * 3 - 1]--;
	info->faces = tmp;
	if (double_face == 4 && slash == 0)
		add_face(line, info, 0, slash);
	return (1);
}

int					get(int fd, t_parse *info)
{
	char			*line;
	int				ret;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			if (!add_vertice(line, info))
				return (0);
		}
		else if (line[0] == 'f')
			if (!add_face(line, info, ft_compte_c(line, ' '),
						ft_compte_c(line, '/')))
				return (0);
		free(line);
	}
	if (ret == -1)
	{
		ft_putendl(strerror(errno));
		return (0);
	}
	return (1);
}

void				calc_color(t_parse *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->nb_vertices * 6)
	{
		info->vertices[i + 3] = ((info->vertices[i] - info->min.x) /
				(info->max.x - info->min.x));
		info->vertices[i + 4] = ((info->vertices[i + 1] - info->min.y) /
				(info->max.y - info->min.y));
		info->vertices[i + 5] = ((info->vertices[i + 2] - info->min.z) /
				(info->max.z - info->min.z));
		info->vertices[i] -= info->center.x;
		info->vertices[i + 1] -= info->center.y;
		info->vertices[i + 2] -= info->center.z;
		i += 6;
	}
}

int					parse(t_env *env, char *file)
{
	int				fd;
	t_parse			info;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putendl(strerror(errno));
		return (0);
	}
	info.nb_face = 0;
	info.nb_vertices = 0;
	info.vertices = (GLfloat*)malloc(sizeof(GLfloat) * info.nb_vertices);
	info.faces = (GLuint*)malloc(sizeof(GLuint) * info.nb_face);
	info.max = vec3_set(0, 0, 0);
	info.min = vec3_set(0, 0, 0);
	if (!get(fd, &info))
	{
		printf("Error in parsing.\n");
		return (0);
	}
	info.center = vec3_mulf(vec3_add(info.max, info.min), 0.5f);
	calc_color(&info);
	close(fd);
	env->info = info;
	return (1);
}
