/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:10:53 by jloro             #+#    #+#             */
/*   Updated: 2019/04/16 14:14:50 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

int	createShader(GLuint *shader, GLenum shaderType, const char * source)
{
	int success;
	char infoLog[512];

	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, 1, &source, NULL);
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		ft_putstr("ERROR::SHADER::COMPILATION_FAILED::");
		ft_putendl(infoLog);
		return (0);
	}
	return (1);
}

char *			readShader(char *file)
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
	read(fd, line, len);
	line[len] = '\0';
	return (line);
}

/*
** 1 = vertexShader, 2 = fragmentShader
*/

int			compileShader(t_env *env)
{
	GLuint	shader[2];
	char	*shaderSource[2];
	int		success;
	char	infoLog[512];

	ft_putendl("Compile Shader");
	if ((shaderSource[0] = readShader("shaders/vertexShader.glsl")) == NULL)
		return (0);
	if ((shaderSource[1] = readShader("shaders/fragShader.glsl")) == NULL)
		return (0);
	createShader(&(shader[0]), GL_VERTEX_SHADER, shaderSource[0]);
	createShader(&(shader[1]), GL_FRAGMENT_SHADER, shaderSource[1]);
	env->shaderProgram = glCreateProgram();
	glAttachShader(env->shaderProgram, shader[0]);
	glAttachShader(env->shaderProgram, shader[1]);
	glLinkProgram(env->shaderProgram);
	glGetProgramiv(env->shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(env->shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n%s", infoLog);
		return (0);
	}
	glDeleteShader(shader[0]);
	glDeleteShader(shader[1]);
	ft_putendl("Finish");
	return (1);
}
