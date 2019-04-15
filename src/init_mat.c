/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:46:51 by jloro             #+#    #+#             */
/*   Updated: 2019/04/15 17:32:54 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include "scop.h"
#include <math.h>

void	addMat4f(char *name, t_mat4 mat, GLboolean transpose, t_env *env)
{
	GLuint  loc;
	loc = glGetUniformLocation(env->shaderProgram, name);
	glUniformMatrix4fv(loc, 1, transpose, mat.m);
}

t_mat4		mat4_proj(void)
{
	t_mat4	ret;
	float	t;
	float	r;
	
	t = tan(degtorad(FOV) / 2) * N_PLANE;
	r = t * WIDTH_SCREEN / HEIGHT_SCREEN;
	ret = mat4_set(0.0f, 0); 
	ret.m[0] = 1 / r;
	ret.m[5] = 1 / t;
	ret.m[10] = -(F_PLANE + N_PLANE) / (F_PLANE - N_PLANE);
	ret.m[11] = -(2 * F_PLANE * N_PLANE) / (F_PLANE - N_PLANE);
	ret.m[14] = -1;
	return (ret);
}

void		init_mat(t_env *env)
{
	t_mat4	proj;
	t_mat4	view;

	proj = mat4_proj();
	view = mat4_set(1.0f, 1);
	view = mat4_look_at(vec3_set(0.0f, 1.0f, 0.0f), vec3_set(0.0f, 0.0f, 0.0f), vec3_set(0.0f, 0.0f, 10.0f));
	env->mvp = mat4_set(1.0f, 1);//mat4_mul(mat4_transpose(&proj), view);
}
