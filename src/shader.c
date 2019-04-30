/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:10:53 by jloro             #+#    #+#             */
/*   Updated: 2019/04/30 13:33:38 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include <stdio.h>

void		shader(GLFWwindow *window, t_env *env)
{
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && env->keys.shader.key)
	{
		printf("Compile shader.\n");
		compile_shader(env);
		printf("Done.\n");
		env->keys.shader.key = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE && !env->keys.shader.key)
		env->keys.shader.key = 1;
}

int			create_program(t_env *env, GLuint shader[2])
{
	int		success;
	char	infolog[512];

	env->shader_program = glCreateProgram();
	glAttachShader(env->shader_program, shader[0]);
	glAttachShader(env->shader_program, shader[1]);
	glLinkProgram(env->shader_program);
	glGetProgramiv(env->shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(env->shader_program, 512, NULL, infolog);
		printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n%s", infolog);
		return (0);
	}
	return (1);
}

int			create_shader(GLuint *shader, GLenum shader_type,
				const char *source)
{
	int		success;
	char	infolog[512];

	*shader = glCreateShader(shader_type);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, infolog);
		printf("ERROR::SHADER::COMPILATION_FAILED::%s \n", infolog);
		return (0);
	}
	return (1);
}

char		*read_shader(char *file)
{
	int		fd;
	int		len;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if ((line = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	if (read(fd, line, len) == -1)
		return (0);
	line[len] = '\0';
	return (line);
}

/*
** 1 = vertexShader, 2 = fragmentShader
*/

int			compile_shader(t_env *env)
{
	GLuint	shader[2];
	char	*shader_source[2];

	if ((shader_source[0] = read_shader("shaders/vertexShader.glsl")) == NULL
			|| ((shader_source[1] = read_shader("shaders/fragShader.glsl")) ==
				NULL))
	{
		printf("Can't find shader files.\n");
		return (0);
	}
	create_shader(&(shader[0]), GL_VERTEX_SHADER, shader_source[0]);
	create_shader(&(shader[1]), GL_FRAGMENT_SHADER, shader_source[1]);
	create_program(env, shader);
	glDeleteShader(shader[0]);
	glDeleteShader(shader[1]);
	free(shader_source[0]);
	free(shader_source[1]);
	return (1);
}
