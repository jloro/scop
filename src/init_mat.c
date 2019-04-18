/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:46:51 by jloro             #+#    #+#             */
/*   Updated: 2019/04/18 14:45:20 by jloro            ###   ########.fr       */
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

void			init_cam(t_mat4 *cam, const t_vec3 up,const t_vec3 target,
		const t_vec3 pos)
{
	t_vec3		cameraUp;
	t_vec3		cameraRight;
	t_vec3		cameraDir;

	cameraDir = vec3_normalize(vec3_sub(pos, target));
	cameraRight = vec3_normalize(vec3_cross_product(up, cameraDir));
	cameraUp = vec3_normalize(vec3_cross_product(cameraDir, cameraRight));
	cam->m[0] = cameraRight.x;
	cam->m[1] = cameraUp.x;
	cam->m[2] = cameraDir.x;
	cam->m[4] = cameraRight.y;
	cam->m[5] = cameraUp.y;
	cam->m[6] = cameraDir.y;
	cam->m[8] = cameraRight.z;
	cam->m[9] = cameraUp.z;
	cam->m[10] = cameraDir.z;
	cam->m[12] = -vec3_dot_product(cameraRight, pos);
	cam->m[13] = -vec3_dot_product(cameraUp, pos);
	cam->m[14] = -vec3_dot_product(cameraDir, pos);
}

t_mat4			mat4_look_at(const t_vec3 up,const t_vec3 target,
		const t_vec3 pos)
{
	t_mat4		cam;

	cam = mat4_set(1.0f, 1);
	init_cam(&cam, up, target, pos);
	return (cam);
}

void		init_mat(t_env *env)
{
	t_mat4	proj;
	t_mat4	view;

	proj = mat4_proj();
	view = mat4_set(1.0f, 1);
	env->model = mat4_set(1.0f, 1);
	view = mat4_look_at(vec3_set(0.0f, 1.0f, 0.0f), vec3_set(0.0f, 0.0f, 0.0f), vec3_set(1.0f, 0.0f, 10.0f));
	env->vp = mat4_mul(view, proj);
	env->vpLoc = glGetUniformLocation(env->shaderProgram, "vp");
	env->modelLoc = glGetUniformLocation(env->shaderProgram, "model");
}
