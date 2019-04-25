/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:46:10 by jloro             #+#    #+#             */
/*   Updated: 2019/04/25 11:48:36 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void resize_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	shader(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && env->keys.shader.key)
	{
		compile_shader(env);
		env->keys.shader.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE && !env->keys.shader.key)
		env->keys.shader.key = 1;
}

void	key_once(GLFWwindow *window, t_key *key, int keycode)
{
	if (glfwGetKey(window, keycode) == GLFW_PRESS && key->key)
	{
		key->active = !key->active;
		key->key = 0;
	}
	if (glfwGetKey(window, keycode) == GLFW_RELEASE && !key->key)
		key->key = 1;
}

void	change_rotate(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && env->keys.x.key)
	{
		env->rotate = vec3_set(1.0f, 0.0f, 0.0f);
		env->keys.x.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE && !env->keys.x.key)
		env->keys.x.key = 1;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS && env->keys.y.key)
	{
		env->rotate = vec3_set(0.0f, 1.0f, 0.0f);
		env->keys.y.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_RELEASE && !env->keys.y.key)
		env->keys.y.key = 1;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && env->keys.z.key)
	{
		env->rotate = vec3_set(0.0f, 0.0f, 1.0f);
		env->keys.z.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE && !env->keys.z.key)
		env->keys.z.key = 1;
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS && env->keys.decrease_speed.key)
	{
		env->rotate_speed -= 0.5;
		env->keys.decrease_speed.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE && !env->keys.decrease_speed.key)
		env->keys.decrease_speed.key = 1;

	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS && env->keys.increase_speed.key)
	{
		env->rotate_speed += 0.5;
		env->keys.increase_speed.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE && !env->keys.increase_speed.key)
		env->keys.increase_speed.key = 1;
}

void key(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	key_once(window, &env->keys.polygon, GLFW_KEY_P);
	key_once(window, &env->keys.move, GLFW_KEY_M);
	key_once(window, &env->keys.texture, GLFW_KEY_T);
	key_once(window, &env->keys.flat, GLFW_KEY_F);
	change_rotate(window, env);
	shader(window, env);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, MOVE_SPEED, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, -MOVE_SPEED, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		env->model = mat4_trans(env->model, -MOVE_SPEED, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		env->model = mat4_trans(env->model, MOVE_SPEED, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, 0.0f, -MOVE_SPEED);
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		env->model = mat4_trans(env->model, 0.0f, 0.0f, MOVE_SPEED);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		env->model = mat4_set(1.0f, 1);
}

