/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:41:12 by jloro             #+#    #+#             */
/*   Updated: 2019/04/15 17:40:38 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "libft.h"
#include "scop.h"
#include "libmat.h"

int			loop(t_env *env)
{
	t_mat4	trans;

	ft_putendl("start loop");
	while (!glfwWindowShouldClose(env->window))
	{
		key(env->window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(env->shaderProgram);
		//float radius = 10.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;

		trans = mat4_set(1.0f, 1);
		//trans = mat4_rot(trans, (float)glfwGetTime(), vec3_set(0.0f, 1.0f, 0.0f));
		addMat4f("mvp", env->mvp, GL_FALSE, env);
		addMat4f("transform", trans, GL_TRUE, env);
		glBindVertexArray(env->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(env->window);
		glfwPollEvents();
	}

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
	(void)argv;
	if (!initGlfw(&env))
		return (0);
	parse(&env, argv[1]);
	compileShader(&env);
	loop(&env);
	return (1);
}
