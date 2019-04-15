/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:46:10 by jloro             #+#    #+#             */
/*   Updated: 2019/04/15 16:29:57 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void resize_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void key(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}
