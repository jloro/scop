/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:46:51 by jloro             #+#    #+#             */
/*   Updated: 2019/04/30 13:39:06 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmat.h"
#include "scop.h"
#include <math.h>

t_mat4		mat4_proj(t_env env)
{
	t_mat4	ret;
	float	t;
	float	r;

	t = tan(degtorad(FOV) / 2) * N_PLANE;
	r = t * (env.width / env.height);
	ret = mat4_set(0.0f, 0);
	ret.m[0] = N_PLANE / r;
	ret.m[5] = N_PLANE / t;
	ret.m[10] = -(F_PLANE + N_PLANE) / (F_PLANE - N_PLANE);
	ret.m[14] = -(2 * F_PLANE * N_PLANE) / (F_PLANE - N_PLANE);
	ret.m[11] = -1;
	return (ret);
}

void		init_cam(t_mat4 *cam, const t_vec3 up, const t_vec3 target,
				const t_vec3 pos)
{
	t_vec3	camera_up;
	t_vec3	camera_right;
	t_vec3	camera_dir;

	camera_dir = vec3_normalize(vec3_sub(pos, target));
	camera_right = vec3_normalize(vec3_cross_product(up, camera_dir));
	camera_up = vec3_normalize(vec3_cross_product(camera_dir, camera_right));
	cam->m[0] = camera_right.x;
	cam->m[1] = camera_up.x;
	cam->m[2] = camera_dir.x;
	cam->m[4] = camera_right.y;
	cam->m[5] = camera_up.y;
	cam->m[6] = camera_dir.y;
	cam->m[8] = camera_right.z;
	cam->m[9] = camera_up.z;
	cam->m[10] = camera_dir.z;
	cam->m[12] = -vec3_dot_product(camera_right, pos);
	cam->m[13] = -vec3_dot_product(camera_up, pos);
	cam->m[14] = -vec3_dot_product(camera_dir, pos);
}

t_mat4		mat4_look_at(const t_vec3 up, const t_vec3 target,
					const t_vec3 pos)
{
	t_mat4	cam;

	cam = mat4_set(1.0f, 1);
	init_cam(&cam, up, target, pos);
	return (cam);
}

void		init_mat(t_env *env)
{
	t_mat4	proj;
	t_mat4	view;

	proj = mat4_proj(*env);
	view = mat4_set(1.0f, 1);
	env->model = mat4_set(1.0f, 1);
	view = mat4_look_at(vec3_set(0.0f, 1.0f, 0.0f), vec3_set(0.0f, 0.0f, 0.0f),
			vec3_set(0.0f, 0.0f, 3.0f));
	env->vp = mat4_mul(view, proj);
	env->vp_loc = glGetUniformLocation(env->shader_program, "vp");
	env->model_loc = glGetUniformLocation(env->shader_program, "model");
	env->tex_loc = glGetUniformLocation(env->shader_program, "texOn");
	env->flat_loc = glGetUniformLocation(env->shader_program, "f");
}
