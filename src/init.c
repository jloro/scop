/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:57:29 by jloro             #+#    #+#             */
/*   Updated: 2019/04/19 16:57:30 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glad.h"
#include "scop.h"
#include "libft.h"
#include "xpm.h"

int					init_texture(t_env *env)
{
	unsigned char	*data;
	int				w;
	int				h;

	glGenTextures(1, &env->texture);
	glBindTexture(GL_TEXTURE_2D, env->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	ft_putendl("Start load texture");
	if ((data = loadxpm("cat.xpm", &w, &h)) == NULL)
	{
		ft_putendl("Error while loading texture");
		return (0);
	}
	ft_putendl("Finish");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE,
			data);
	glGenerateMipmap(GL_TEXTURE_2D);
	free(data);
	return (1);
}

int					initglfw(t_env *env)
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

void				init_keys(t_env *env)
{
	env->keys.polygon.active = 0;
	env->keys.polygon.key = 0;
	env->keys.move.active = 1;
	env->keys.move.key = 0;
	env->keys.shader.key = 0;
	env->keys.shader.active = 0;
	env->keys.x.key = 0;
	env->keys.x.active = 0;
	env->keys.y.key = 0;
	env->keys.y.active = 1;
	env->keys.z.key = 0;
	env->keys.z.active = 0;
	env->keys.texture.key = 0;
	env->keys.texture.active = 0;
	env->keys.increase_speed.key = 0;
	env->keys.decrease_speed.active = 0;
	env->rotate = vec3_set(0.0f, 1.0f, 0.0f);
	env->rotate_speed = 0.5f;
}

int					init(t_env *env)
{
	init_keys(env);
	if (!initglfw(env) || !init_texture(env))
		return (0);
	send_opengl(&env->info, env);
	free(env->info.vertices);
	free(env->info.faces);
	return (1);
}
