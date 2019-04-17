/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:04:36 by jloro             #+#    #+#             */
/*   Updated: 2019/04/17 13:45:54 by jloro            ###   ########.fr       */
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

int			sendOpenGL(t_parse *info, t_env *env)
{
	ft_putendl("Send vertices/face to openCL");
	glGenVertexArrays(1, &env->VAO);
	glGenBuffers(1, &env->VBO);
	glGenBuffers(1, &env->EBO);

	glBindVertexArray(env->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, env->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * info->nbVertices * 3, info->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * info->nbFace * 3, info->faces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	ft_putendl("Finish");
	return (1);
}

int			addVertice(char *line, t_parse *info)
{
	float	*tmp;
	unsigned int	i;

	i = -1;
	info->nbVertices++;
	if ((tmp = (float*)malloc(sizeof(float) * info->nbVertices * 3)) == NULL)
		return (0);
	while (++i < (info->nbVertices - 1) * 3)
		tmp[i] = info->vertices[i];
	free(info->vertices);
	if (!sscanf(line, "v %f %f %f", &tmp[info->nbVertices * 3 - 3],
				&tmp[info->nbVertices * 3 - 2], &tmp[info->nbVertices * 3 - 1]))
		return (0);
	info->vertices = tmp;
	return (1);
}

int			addFace(char *line, t_parse *info, int double_face)
{
	unsigned int	*tmp;
	unsigned int	tmp2;
	unsigned int	i;

	i = -1;
	info->nbFace++;
	if ((tmp = (unsigned int*)malloc(sizeof(unsigned int) * info->nbFace * 3)) == NULL)
		return (0);
	while (++i < (info->nbFace - 1) * 3)
		tmp[i] = info->faces[i];
	free(info->faces);
	if (double_face == 3 && !sscanf(line, "f %u %u %u",
				&tmp[info->nbFace * 3 - 3], &tmp[info->nbFace * 3 - 2]
				, &tmp[info->nbFace * 3 - 1]))
		return (0);
	else if (double_face == 4 &&!sscanf(line, "f %u %u %u %u", &tmp[info->nbFace * 3 - 3],
				&tmp[info->nbFace * 3 - 2], &tmp[info->nbFace * 3 - 1], &tmp2))
		return (0);
	else if (double_face == 0 &&!sscanf(line, "f %u %u %u %u", &tmp2, &tmp[info->nbFace * 3 - 3],
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

	ft_putendl("Start parsing");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
			addVertice(line, info);
		else if (line[0] == 'f')
			addFace(line, info, ft_compte_c(line, ' '));
		free(line);
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
	info.vertices = (float*)malloc(sizeof(float) * info.nbVertices);
	info.faces = (unsigned int*)malloc(sizeof(unsigned int) * info.nbFace);
	get(fd, &info);
	close(fd);
	printf("%u\n", info.nbFace);
	for (unsigned int i = 0; i < info.nbFace * 3; i+=3)
		printf("%u %u %u\n", info.faces[i], info.faces[i + 1], info.faces[i + 2]);
	sendOpenGL(&info, env);
	free(info.vertices);
	free(info.faces);
	return (0);
}
