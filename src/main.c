/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:04:38 by jloro             #+#    #+#             */
/*   Updated: 2019/04/12 16:15:13 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "libmat.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void leave(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

char *		readShader(char * file)
{
	int fd;
	int len;
	char * string;

	fd = open(file, O_RDONLY);
	len = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	string = (char *)malloc(sizeof(char) * (len + 1));
	read(fd, string, len);
	string[len] = '\0';
	return string;
}

int	createShader(int * shader, GLenum shaderType, const char * source)
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
		printf("ERROR::SHADER::COMPILATION_FAILED\n%s", infoLog);
		return 0;
	}
	return 1;
}

void	initShader(unsigned int * shaderProgram, unsigned int * VAO, unsigned int * EBO, unsigned int * VBO)
{
	int success;
	char infoLog[512];
	char *	vertexShaderSource;
	vertexShaderSource = readShader("shaders/vertexShader.glsl");
	char *	fragmentShaderSource;
	fragmentShaderSource = readShader("shaders/fragShader.glsl");
	float vertices[] = {
		0.5f, 0.75f, 0.0f,
		0.5f, -0.75f, 0.0f,
		-0.5f, -0.75f, 0.0f,
		-0.5f, 0.75f, 0.0f
	};
	unsigned int faces[] = {
		0, 1, 3,
		1, 2, 3
	};
	int vertexShader;
	//createShader(&vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
	int fragmentShader;
	//createShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar *const *)&vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::COMPILATION_FAILED\n%s", infoLog);
	}
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar *const *)&fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR::SHADER::COMPILATION_FAILED\n%s", infoLog);
	}
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);
	glGetProgramiv(*shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n%s", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

unsigned int	loadtexture(int w, int h, unsigned char * data)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	return texture;
}

int main()
{
	t_vec4	vec;
	t_mat4	trans;

	trans = ft_mat4_set(1.0f, 1);
	vec = ft_vec4_set(10.0f, 10.0f, 10.0f, 1.0f);
	trans = ft_mat4_trans(trans, 0.5f, -0.5f, 0.0);
	int i =  0;
	while (i < 16)
	{
		printf("%f ", trans.m[i]);
		i++;
	}
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGl", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return 0;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return 0;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	unsigned int shaderProgram;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int VBO;
	initShader(&shaderProgram, &VAO, &EBO, &VBO);

	while (!glfwWindowShouldClose(window))
	{
		leave(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		trans = ft_mat4_set(1.0f, 1);
		trans = ft_mat4_rot(trans, (float)glfwGetTime(), Z_AXIS);
		trans = ft_mat4_trans(trans, 0.5f, -0.5f, 0.0);
		unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_TRUE, trans.m);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
