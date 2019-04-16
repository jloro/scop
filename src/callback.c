/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:46:10 by jloro             #+#    #+#             */
/*   Updated: 2019/04/16 16:54:12 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void resize_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void key(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		env->polygon = !env->polygon;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, MOVE_SPEED, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, -MOVE_SPEED, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		env->model = mat4_trans(env->model, -MOVE_SPEED, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		env->model = mat4_trans(env->model, MOVE_SPEED, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, 0.0f, MOVE_SPEED);
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, 0.0f, -MOVE_SPEED);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		env->model = mat4_set(1.0f, 1);
}
