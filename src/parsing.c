/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:04:36 by jloro             #+#    #+#             */
/*   Updated: 2019/04/15 17:22:56 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "libft.h"
#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int			sendOpenGL(t_parse *info, t_env *env)
{
	ft_putendl("Send vertex/face to openCL");
	glGenVertexArrays(1, &env->VAO);
	glGenBuffers(1, &env->VBO);
	glGenBuffers(1, &env->EBO);

	glBindVertexArray(env->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, env->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(info->vertex), info->vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(info->faces), info->faces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	ft_putendl("Finish");
	return (1);
}

int			get(int fd, t_parse *info)
{
	char	*line;
	float	tmp[3];
	int		i;

	i = 0;
	ft_putendl("Start parsing");
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v')
		{
			sscanf(line, "v %f %f %f", &tmp[0], &tmp[1], &tmp[2]);
			info->vertex[i] = tmp[0];
			info->vertex[i + 1] = tmp[1];
			info->vertex[i + 2] = tmp[2];
		}
		if (ft_strcmp(line, "") == 0)
		{
			i = 0;
		}
		if (line[0] == 'f')
		{
			sscanf(line, "f %f %f %f", &tmp[0], &tmp[1], &tmp[2]);
			info->faces[i] = tmp[0];
			info->faces[i + 1] = tmp[1];
			info->faces[i + 2] = tmp[2];
		}
		free(line);
		i += 3;
	}
	ft_putendl("End parsing");
	return (1);
}

int			count(int fd, t_parse *info)
{
	char	*line;

	info->nbVertex = 0;
	info->nbFace = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v' && line[1] == ' ')
			info->nbVertex++;
		else if (line[0] == 'f' && line[1] == ' ')
			info->nbFace++;
		free(line);
	}
	info->vertex = (float*)malloc(sizeof(float) * info->nbVertex * 3);
	info->faces = (float*)malloc(sizeof(float) * info->nbFace * 3);
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
	count(fd, &info);	
	lseek(fd, 0, SEEK_SET);
	get(fd, &info);
	close(fd);
	sendOpenGL(&info, env);
	free(info.vertex);
	free(info.faces);
	return (0);	
}
