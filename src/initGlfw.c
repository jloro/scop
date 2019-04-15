/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initGlfw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:43:00 by jloro             #+#    #+#             */
/*   Updated: 2019/04/15 15:14:15 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "scop.h"
#include "libft.h"

int		initGlfw(t_env *env)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	env->window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN,
			"Scop", NULL, NULL);
	glfwMakeContextCurrent(env->window);
	if (env->window == NULL)
	{
		ft_putendl("Failed to create GLFW window");
		glfwTerminate();
		return (0);
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ft_putendl("Failed to initialize GLAD");
		glfwTerminate();
		return (0);
	}
	glfwSetFramebufferSizeCallback(env->window, resize_callback);
	return (1);
}
