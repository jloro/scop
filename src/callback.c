/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:46:10 by jloro             #+#    #+#             */
/*   Updated: 2019/04/30 14:57:37 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	change_rotate(GLFWwindow *window, t_env *env, int keycode, t_key *key)
{
	if (glfwGetKey(window, keycode) == GLFW_PRESS && key->key)
	{
		if (keycode == GLFW_KEY_X)
			env->rotate.x = env->rotate.x == 0.0f ? 1.0f : 0.0f;
		else if (keycode == GLFW_KEY_Y)
			env->rotate.y = env->rotate.y == 0.0f ? 1.0f : 0.0f;
		else if (keycode == GLFW_KEY_Z)
			env->rotate.z = env->rotate.z == 0.0f ? 1.0f : 0.0f;
		key->key = 0;
	}
	if (glfwGetKey(window, keycode) == GLFW_RELEASE && !key->key)
		key->key = 1;
}

void	change_rotate_speed(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS &&
			env->keys.decrease_rot_speed.key)
	{
		env->rotate_speed -= 0.5;
		env->keys.decrease_rot_speed.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE &&
			!env->keys.decrease_rot_speed.key)
		env->keys.decrease_rot_speed.key = 1;
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS &&
			env->keys.increase_rot_speed.key)
	{
		env->rotate_speed += 0.5;
		env->keys.increase_rot_speed.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE &&
			!env->keys.increase_rot_speed.key)
		env->keys.increase_rot_speed.key = 1;
}

void	change_move_speed(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS &&
			env->keys.decrease_move_speed.key)
	{
		env->move_speed = env->move_speed == 0.25f ? env->move_speed :
			env->move_speed / 2;
		env->keys.decrease_move_speed.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_RELEASE &&
			!env->keys.decrease_move_speed.key)
		env->keys.decrease_move_speed.key = 1;
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS &&
			env->keys.increase_move_speed.key)
	{
		env->move_speed *= 2;
		env->keys.increase_move_speed.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_RELEASE &&
			!env->keys.increase_move_speed.key)
		env->keys.increase_move_speed.key = 1;
}

void	move(int keycode, t_vec3 vec, t_env *env, GLFWwindow *window)
{
	if (glfwGetKey(window, keycode) == GLFW_PRESS)
		env->model = mat4_trans(env->model, vec);
}

void	key(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	key_once(window, &env->keys.polygon, GLFW_KEY_P);
	key_once(window, &env->keys.move, GLFW_KEY_M);
	key_once(window, &env->keys.texture, GLFW_KEY_T);
	key_once(window, &env->keys.flat, GLFW_KEY_F);
	key_once(window, &env->keys.grey, GLFW_KEY_G);
	change_rotate_speed(window, env);
	change_move_speed(window, env);
	change_rotate(window, env, GLFW_KEY_X, &env->keys.x);
	change_rotate(window, env, GLFW_KEY_Y, &env->keys.y);
	change_rotate(window, env, GLFW_KEY_Z, &env->keys.z);
	shader(window, env);
	move(GLFW_KEY_UP, vec3_set(0.0f, env->move_speed, 0.0f), env, window);
	move(GLFW_KEY_DOWN, vec3_set(0.0f, -env->move_speed, 0.0f), env, window);
	move(GLFW_KEY_LEFT, vec3_set(-env->move_speed, 0.0f, 0.0f), env, window);
	move(GLFW_KEY_RIGHT, vec3_set(env->move_speed, 0.0f, 0.0f), env, window);
	move(GLFW_KEY_PAGE_UP, vec3_set(0.0f, 0.0f, -env->move_speed), env,
			window);
	move(GLFW_KEY_PAGE_DOWN, vec3_set(0.0f, 0.0f, env->move_speed), env,
			window);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		env->model = mat4_set(1.0f, 1);
}
