/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:41:12 by jloro             #+#    #+#             */
/*   Updated: 2019/04/18 14:50:20 by jloro            ###   ########.fr       */
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
	env->model = mat4_rot(env->model, degtorad(0.5), vec3_set(0.0f, 1.0f, 0.0f));
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

		if (env->polygon.active)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (env->move.active)
			rotate(env);
		glUseProgram(env->shaderProgram);

		glUniformMatrix4fv(env->vpLoc, 1, GL_FALSE, env->vp.m);
		glUniformMatrix4fv(env->modelLoc, 1, GL_TRUE, env->model.m);

		glBindVertexArray(env->VAO);
		glDrawElements(GL_TRIANGLES, env->nbFace * 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &env->VAO);
	glDeleteBuffers(1, &env->VBO);
	glDeleteBuffers(1, &env->EBO);
	glfwTerminate();
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	env;

	env.polygon.active = 0;
	env.polygon.key = 0;
	env.move.active = 1;
	env.move.key = 0;
	env.shader.key = 0;
	env.shader.active = 0;
	if (argc != 2)
	{
		ft_putendl("Usage: ./scop file");
		return (0);
	}
	(void)argv;
	if (!initGlfw(&env))
		return (0);
	parse(&env, argv[1]);
	if (!compileShader(&env))
		return (0);
	init_mat(&env);
	loop(&env);
	return (1);
}
