/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:41:12 by jloro             #+#    #+#             */
/*   Updated: 2019/04/19 15:14:05 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "libft.h"
#include "scop.h"
#include "libmat.h"
#include <math.h>
#include <stdio.h>

void		rotate(t_env *env)
{
	t_mat4	tmp;

	tmp = mat4_cpy(env->model);
	env->model.m[3] = 0;
	env->model.m[7] = 0;
	env->model.m[11] = 0;
	env->model = mat4_rot(env->model, degtorad(env->rotate_speed), env->rotate);
	env->model.m[3] = tmp.m[3];
	env->model.m[7] = tmp.m[7];
	env->model.m[11] = tmp.m[11];
}

int			loop(t_env *env)
{
	ft_putendl("start loop");
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(env->window))
	{
		key(env->window, env);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (env->keys.polygon.active)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (env->keys.move.active && !vec3_is_null(env->rotate))
			rotate(env);
		glUseProgram(env->shaderProgram);

		glBindTexture(GL_TEXTURE_2D, env->texture);

		glUniformMatrix4fv(env->vpLoc, 1, GL_FALSE, env->vp.m);
		glUniformMatrix4fv(env->modelLoc, 1, GL_TRUE, env->model.m);

		glUniform1i(env->texLoc, env->keys.texture.active);

		glBindVertexArray(env->VAO);
		glDrawElements(GL_TRIANGLES, env->info.nbFace * 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &env->VAO);
	glDeleteBuffers(1, &env->VBO);
	glDeleteBuffers(1, &env->EBO);
	glfwTerminate();
	ft_putendl("end loop");
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
	{
		ft_putendl("Usage: ./scop file");
		return (0);
	}
	init_keys(&env);
	if (!initGlfw(&env))
		return (0);
	if (!parse(&env, argv[1]))
		return (0);
	if (!compileShader(&env))
		return (0);
	init_mat(&env);
	loop(&env);
	return (1);
}
