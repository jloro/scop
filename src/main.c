/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:41:12 by jloro             #+#    #+#             */
/*   Updated: 2019/04/16 16:52:24 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "libft.h"
#include "scop.h"
#include "libmat.h"
#include <math.h>
#include <stdio.h>
int			loop(t_env *env)
{
	ft_putendl("start loop");
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(env->window))
	{
		env->trans = mat4_set(1.0f, 1);
		key(env->window, env);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (env->polygon)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glUseProgram(env->shaderProgram);

		env->trans = mat4_rot(env->trans, (float)glfwGetTime(), vec3_set(0.0f, 1.0f, 0.0f));
		env->trans = mat4_rot(env->trans, (float)glfwGetTime(), vec3_set(1.0f, 0.0f, 0.0f));
		env->trans = mat4_rot(env->trans, (float)glfwGetTime(), vec3_set(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(env->transformLoc, 1, GL_TRUE, env->trans.m);
		glUniformMatrix4fv(env->vpLoc, 1, GL_FALSE, env->vp.m);
		glUniformMatrix4fv(env->modelLoc, 1, GL_TRUE, env->model.m);

		glBindVertexArray(env->VAO);
		glDrawElements(GL_TRIANGLES, env->nbFace * 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}
	return (1);
}

int			main(int argc, char **argv)
{
	t_env	env;

	env.polygon = 0;
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
