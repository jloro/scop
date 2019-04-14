/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:04:38 by jloro             #+#    #+#             */
/*   Updated: 2019/04/14 16:02:06 by jules            ###   ########.fr       */
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

#define WIDTH_SCREEN 800
#define HEIGHT_SCREEN 600
#define F_PLANE 100.0f
#define N_PLANE 0.1f
#define FOV 90.0f
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
	(void)EBO;
	int success;
	char infoLog[512];
	char *	vertexShaderSource;
	vertexShaderSource = readShader("shaders/vertexShader.glsl");
	char *	fragmentShaderSource;
	fragmentShaderSource = readShader("shaders/fragShader.glsl");
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
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

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
	t_mat4	trans;
	t_mat4	proj;
	t_mat4	model;
	t_mat4	view;
	float	t = tan(degtorad(FOV / 2)) * N_PLANE;
	float	ar = WIDTH_SCREEN / HEIGHT_SCREEN;
	float r = t * ar;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "LearnOpenGl", NULL, NULL);
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

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		leave(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shaderProgram);
		proj = mat4_set(0.0f, 0);
		model = mat4_set(1.0f, 1);
		trans = mat4_set(1.0f, 1);
		view = mat4_set(1.0f, 1);
        trans = mat4_trans(trans, 0.0f, 0.0f, -10.0f);
		view = mat4_look_at(vec3_set(0.0f, 1.0f, 0.0f), vec3_set(0.0f, 0.0f, 0.0f), vec3_set(0.0f, 0.0f, 3.0f));
		proj.m[0] = 1 / r;
		proj.m[5] = 1 / t;
		proj.m[10] = -(F_PLANE + N_PLANE) / (F_PLANE - N_PLANE);
		proj.m[11] = -(2 * F_PLANE * N_PLANE) / (F_PLANE - N_PLANE);
		proj.m[14] = -1;

		unsigned int transLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transLoc, 1, GL_TRUE, trans.m);
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.m);
		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_TRUE, model.m);
		unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj.m);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
