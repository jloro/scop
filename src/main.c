/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 11:04:38 by jloro             #+#    #+#             */
/*   Updated: 2019/04/10 18:23:32 by jloro            ###   ########.fr       */
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

int	createShader(unsigned int * shader, GLenum shaderType, const char * source)
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
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
		return 0;
	}
	return 1;
}

void	initShader(unsigned int * shaderProgram, unsigned int * VAO, unsigned int * VBO)
{
	int success;
	char infoLog[512];
	char *	vertexShaderSource;
	vertexShaderSource = readShader("shaders/vertexShader.glsl");
	char *	fragmentShaderSource;
	fragmentShaderSource = readShader("shaders/fragShader.glsl");
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,
	};
	unsigned int vertexShader;
	createShader(&vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader;
	createShader(&fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource);
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glGetProgramiv(*shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		printf("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n%s", infoLog);
	}
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glBindVertexArray(*VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main()
{
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
	unsigned int VBO;
	initShader(&shaderProgram, &VAO, &VBO);
	while (!glfwWindowShouldClose(window))
	{
		leave(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
