/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:04:36 by jloro             #+#    #+#             */
/*   Updated: 2019/04/19 15:05:26 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "libft.h"
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
	info->min.x = info->min.x < tmp[info->nbVertices * 6 - 6] ? info->min.x : tmp[info->nbVertices * 6 - 6];
	info->max.x = info->max.x > tmp[info->nbVertices * 6 - 6] ? info->max.x : tmp[info->nbVertices * 6 - 6];
	info->min.y = info->min.y < tmp[info->nbVertices * 6 - 5] ? info->min.y : tmp[info->nbVertices * 6 - 5];
	info->max.y = info->max.y > tmp[info->nbVertices * 6 - 5] ? info->max.y : tmp[info->nbVertices * 6 - 5];
	info->min.z = info->min.z < tmp[info->nbVertices * 6 - 4] ? info->min.z : tmp[info->nbVertices * 6 - 4];
	info->max.z = info->max.z > tmp[info->nbVertices * 6 - 4] ? info->max.z : tmp[info->nbVertices * 6 - 4];
}

int			sendOpenGL(t_parse *info, t_env *env)
{
	ft_putendl("Send vertices/face to openCL");
	glGenVertexArrays(1, &env->VAO);
	glGenBuffers(1, &env->VBO);
	glGenBuffers(1, &env->EBO);

	glBindVertexArray(env->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, env->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * info->nbVertices * 6, info->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * info->nbFace * 3,info->faces, GL_STATIC_DRAW);

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
	info->nbVertices++;
	if ((tmp = (GLfloat*)malloc(sizeof(GLfloat) * info->nbVertices * 6)) == NULL)
		return (0);
	while (++i < (info->nbVertices - 1) * 6)
		tmp[i] = info->vertices[i];
	free(info->vertices);
	if (!sscanf(line, "v %f %f %f", &tmp[info->nbVertices * 6 - 6],
				&tmp[info->nbVertices * 6 - 5], &tmp[info->nbVertices * 6 - 4]))
		return (0);
	tmp[info->nbVertices * 6 - 3] = -1;
	tmp[info->nbVertices * 6 - 2] = -1;
	tmp[info->nbVertices * 6 - 1] = -1;
	calc_max_min(info, tmp);
	info->vertices = tmp;
	return (1);
}

int			addFace(char *line, t_parse *info, int double_face)
{
	GLuint	*tmp;
	GLuint	tmp2;
	unsigned int	i;

	i = -1;
	info->nbFace++;
	if ((tmp = (GLuint*)malloc(sizeof(GLuint) * info->nbFace * 3)) == NULL)
		return (0);
	while (++i < (info->nbFace - 1) * 3)
		tmp[i] = info->faces[i];
	free(info->faces);
	if (double_face == 3 && !sscanf(line, "f %u %u %u",
				&tmp[info->nbFace * 3 - 3], &tmp[info->nbFace * 3 - 2]
				, &tmp[info->nbFace * 3 - 1]))
		return (0);
	else if (double_face == 4 && !sscanf(line, "f %u %u %u %u", &tmp[info->nbFace * 3 - 3],
				&tmp[info->nbFace * 3 - 2], &tmp[info->nbFace * 3 - 1], &tmp2))
		return (0);
	else if (double_face == 0 && !sscanf(line, "f %u %u %u %u", &tmp[info->nbFace * 3 - 3], &tmp2, 
				&tmp[info->nbFace * 3 - 2], &tmp[info->nbFace * 3 - 1]))
		return (0);
	tmp[info->nbFace * 3 - 3]--;
	tmp[info->nbFace * 3 - 2]--;
	tmp[info->nbFace * 3 - 1]--;
	info->faces = tmp;
	if (double_face == 4)
		addFace(line, info, 0);
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
			addVertice(line, info);
		else if (line[0] == 'f')
			addFace(line, info, ft_compte_c(line, ' '));
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
	info.nbFace = 0;
	info.nbVertices = 0;
	info.vertices = (GLfloat*)malloc(sizeof(GLfloat) * info.nbVertices);
	info.faces = (GLuint*)malloc(sizeof(GLuint) * info.nbFace);
	info.max.y = 0;
	info.min.y = 0;
	info.max.x = 0;
	info.min.x = 0;
	info.max.z = 0;
	info.min.z = 0;
	if (!get(fd, &info))
		return (0);
	info.center = vec3_mulf(vec3_add(info.max, info.min), 0.5f);
	for (unsigned int i = 0; i < info.nbVertices * 6; i += 6)
	{
		info.vertices[i + 3] = ((info.vertices[i] - info.min.y) / (info.max.y - info.min.y));
		info.vertices[i + 4] = ((info.vertices[i + 1] - info.min.y) / (info.max.y - info.min.y));
		info.vertices[i + 5] = ((info.vertices[i + 2] - info.min.y) / (info.max.y - info.min.y));
		info.vertices[i] -= info.center.x;
		info.vertices[i + 1] -= info.center.y;
		info.vertices[i + 2] -= info.center.z;
	}
	//for (unsigned int i = 0; i < info.nbVertices * 6; i += 6)
	//	printf("%f %f %f    %f %f %f\n", info.vertices[i], info.vertices[i + 1], info.vertices[i + 2], info.vertices[i + 3], info.vertices[i + 4], info.vertices[i + 5]);
	close(fd);
	sendOpenGL(&info, env);
	free(info.vertices);
	free(info.faces);
	env->info = info;
	return (1);
}
