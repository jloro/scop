/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:46:51 by jloro             #+#    #+#             */
/*   Updated: 2019/04/16 16:37:15 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include "scop.h"
#include <math.h>

t_mat4		mat4_proj(void)
{
	t_mat4	ret;
	float	t;
	float	r;
	
	t = tan(degtorad(FOV) / 2) * N_PLANE;
	r = t * (WIDTH_SCREEN / HEIGHT_SCREEN);
	ret = mat4_set(0.0f, 0); 
	ret.m[0] = 1 / r;
	ret.m[5] = 1 / t;
	ret.m[10] = -(F_PLANE + N_PLANE) / (F_PLANE - N_PLANE);
	ret.m[14] = -(2 * F_PLANE * N_PLANE) / (F_PLANE - N_PLANE);
	ret.m[11] = -1;
	return (ret);
}

void		init_mat(t_env *env)
{
	t_mat4	proj;
	t_mat4	view;

	proj = mat4_proj();
	view = mat4_set(1.0f, 1);
	env->model = mat4_set(1.0f, 1);
	view = mat4_look_at(vec3_set(0.0f, 1.0f, 0.0f), vec3_set(0.0f, 0.0f, 0.0f), vec3_set(1.0f, 0.0f, 30.0f));
	env->vp = mat4_mul(view, proj);
	env->vpLoc = glGetUniformLocation(env->shaderProgram, "vp");
	env->modelLoc = glGetUniformLocation(env->shaderProgram, "model");
	env->transformLoc = glGetUniformLocation(env->shaderProgram, "transform");
}
