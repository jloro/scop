/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:48:42 by jloro             #+#    #+#             */
/*   Updated: 2019/04/29 18:04:26 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "scop.h"
#include "libmat.h"
#include <stdio.h>

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
	printf("Send vertices/face to openCL\n");
	glGenVertexArrays(1, &env->vao);
	glGenBuffers(1, &env->vbo);
	glGenBuffers(1, &env->ebo);
	glBindVertexArray(env->vao);
	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * info->nb_vertices * 6,
			info->vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * info->nb_face * 3,
			info->faces, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			(void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			(void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	printf("Finish\n");
	return (1);
}

int			add_face_if(int select[2], char *line, t_parse *info,
						GLuint *tmp)
{
	GLuint	tmp2[9];

	if (select[1] == 0 && select[0] == 3 && !sscanf(line, "f %u %u %u",
				&tmp[info->nb_face * 3 - 3], &tmp[info->nb_face * 3 - 2]
				, &tmp[info->nb_face * 3 - 1]))
		return (0);
	else if (select[1] == 0 && select[0] == 4 && !sscanf(line, "f %u %u %u %u",
				&tmp[info->nb_face * 3 - 3], &tmp[info->nb_face * 3 - 2],
				&tmp[info->nb_face * 3 - 1], &tmp2[0]))
		return (0);
	else if (select[1] == 0 && select[0] == 0 && !sscanf(line, "f %u %u %u %u",
				&tmp[info->nb_face * 3 - 3], &tmp2[0],
				&tmp[info->nb_face * 3 - 2], &tmp[info->nb_face * 3 - 1]))
		return (0);
	if (select[1] == 3 && !sscanf(line, "f %u/%u %u/%u %u/%u",
				&tmp[info->nb_face * 3 - 3], &tmp2[0],
				&tmp[info->nb_face * 3 - 2], &tmp2[1],
				&tmp[info->nb_face * 3 - 1], &tmp2[2]))
		return (0);
	else if (select[1] == 6 && !sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u",
				&tmp[info->nb_face * 3 - 3], &tmp2[0], &tmp2[1],
				&tmp[info->nb_face * 3 - 2], &tmp2[2], &tmp2[3],
				&tmp[info->nb_face * 3 - 1], &tmp2[4], &tmp2[5]))
		return (0);
	return (1);
}
