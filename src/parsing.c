/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:04:36 by jloro             #+#    #+#             */
/*   Updated: 2019/04/29 16:29:57 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
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

void		calc_max_min(t_parse *info, GLfloat *tmp)
{
	info->min.x = minf(info->min.x, tmp[info->nb_vertices * 6 - 6]);
	info->max.x = maxf(info->max.x, tmp[info->nb_vertices * 6 - 6]);
	info->min.y = minf(info->min.y, tmp[info->nb_vertices * 6 - 5]);
	info->max.y = maxf(info->max.y, tmp[info->nb_vertices * 6 - 5]);
	info->min.z = minf(info->min.z, tmp[info->nb_vertices * 6 - 4]);
	info->max.z = maxf(info->max.z, tmp[info->nb_vertices * 6 - 4]);
}

int			send_opengl(t_parse *info, t_env *env)
{
	ft_putendl("Send vertices/face to openCL");
	glGenVertexArrays(1, &env->vao);
	glGenBuffers(1, &env->vbo);
	glGenBuffers(1, &env->ebo);

	glBindVertexArray(env->vao);

	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * info->nb_vertices * 6, info->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * info->nb_face * 3,info->faces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	ft_putendl("Finish");
	return (1);
}

int			addVertice(char *line, t_parse *info)
{
	GLfloat	*tmp;
	unsigned int	i;

	i = -1;
	info->nb_vertices++;
	if ((tmp = (GLfloat*)malloc(sizeof(GLfloat) * info->nb_vertices * 6)) == NULL)
		return (0);
	while (++i < (info->nb_vertices - 1) * 6)
		tmp[i] = info->vertices[i];
	free(info->vertices);
	if (!sscanf(line, "v %f %f %f", &tmp[info->nb_vertices * 6 - 6],
				&tmp[info->nb_vertices * 6 - 5], &tmp[info->nb_vertices * 6 - 4]))
		return (0);
	tmp[info->nb_vertices * 6 - 3] = -1;
	tmp[info->nb_vertices * 6 - 2] = -1;
	tmp[info->nb_vertices * 6 - 1] = -1;
	calc_max_min(info, tmp);
	info->vertices = tmp;
	return (1);
}

int			addFace(char *line, t_parse *info, int double_face, int slash)
{
	GLuint	*tmp;
	GLuint	tmp2[9];
	unsigned int	i;

	i = -1;
	info->nb_face++;
	if ((tmp = (GLuint*)malloc(sizeof(GLuint) * info->nb_face * 3)) == NULL)
		return (0);
	while (++i < (info->nb_face - 1) * 3)
		tmp[i] = info->faces[i];
	free(info->faces);
	if (slash == 0 && double_face == 3 && !sscanf(line, "f %u %u %u",
				&tmp[info->nb_face * 3 - 3], &tmp[info->nb_face * 3 - 2]
				, &tmp[info->nb_face * 3 - 1]))
		return (0);
	else if (slash == 0 && double_face == 4 && !sscanf(line, "f %u %u %u %u", &tmp[info->nb_face * 3 - 3],
				&tmp[info->nb_face * 3 - 2], &tmp[info->nb_face * 3 - 1], &tmp2[0]))
		return (0);
	else if (slash == 0 && double_face == 0 && !sscanf(line, "f %u %u %u %u", &tmp[info->nb_face * 3 - 3], &tmp2[0], 
				&tmp[info->nb_face * 3 - 2], &tmp[info->nb_face * 3 - 1]))
		return (0);
	if (slash == 3 && !sscanf(line, "f %u/%u %u/%u %u/%u", &tmp[info->nb_face * 3 - 3], &tmp2[0], 
				&tmp[info->nb_face * 3 - 2], &tmp2[1], &tmp[info->nb_face * 3 - 1], &tmp2[2]))
		return (0);
	else if (slash == 6 && !sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u", &tmp[info->nb_face * 3 - 3], &tmp2[0], &tmp2[1], 
				&tmp[info->nb_face * 3 - 2], &tmp2[2], &tmp2[3], &tmp[info->nb_face * 3 - 1], &tmp2[4], &tmp2[5]))
		return (0);
	tmp[info->nb_face * 3 - 3]--;
	tmp[info->nb_face * 3 - 2]--;
	tmp[info->nb_face * 3 - 1]--;
	info->faces = tmp;
	if (double_face == 4 && slash == 0)
		addFace(line, info, 0, slash);
	return (1);
}

int			get(int fd, t_parse *info)
{
	char			*line;
	int				ret;

	ft_putendl("Start parsing");
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			if (!addVertice(line, info))
				return (0);
		}
		else if (line[0] == 'f')
		{
			if (!addFace(line, info, ft_compte_c(line, ' '), ft_compte_c(line, '/')))
				return (0);
		}
		free(line);
	}
	if (ret == -1)
	{
		ft_putendl(strerror(errno));
		return (0);
	}
	ft_putendl("End parsing");
	return (1);
}

int			parse(t_env *env, char *file)
{
	int		fd;
	t_parse	info;

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
		return (0);
	info.center = vec3_mulf(vec3_add(info.max, info.min), 0.5f);
	for (unsigned int i = 0; i < info.nb_vertices * 6; i += 6)
	{
		info.vertices[i + 3] = ((info.vertices[i] - info.min.y) / (info.max.y - info.min.y));
		info.vertices[i + 4] = ((info.vertices[i + 1] - info.min.y) / (info.max.y - info.min.y));
		info.vertices[i + 5] = ((info.vertices[i + 2] - info.min.y) / (info.max.y - info.min.y));
		info.vertices[i] -= info.center.x;
		info.vertices[i + 1] -= info.center.y;
		info.vertices[i + 2] -= info.center.z;
	}
	close(fd);
	env->info = info;
	return (1);
}
