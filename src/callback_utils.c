/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:55:30 by jloro             #+#    #+#             */
/*   Updated: 2019/04/30 11:56:57 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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

void	resize_callback(GLFWwindow *window, t_env *env)
{
	glfwGetFramebufferSize(window, &env->width, &env->height);
	glViewport(0, 0, env->width, env->height);
	refresh(env);
}
