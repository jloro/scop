/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:32:44 by jloro             #+#    #+#             */
/*   Updated: 2019/04/15 17:16:47 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPE_H
# define SCOPE_H

# include <GLFW/glfw3.h>
# include "libmat.h"

# define WIDTH_SCREEN 800.0f
# define HEIGHT_SCREEN 600.0f
# define F_PLANE 100.0f
# define N_PLANE 0.1f
# define FOV 90.0f

typedef struct	s_env
{
	GLFWwindow	*window;
	GLuint		shaderProgram;
	GLuint		VAO;
	GLuint		VBO;
	GLuint		EBO;
	t_mat4		mvp;
}				t_env;

typedef struct	s_parse
{
	float		*vertex;
	int			nbVertex;
	float		*faces;
	int			nbFace;
}				t_parse;

void	resize_callback(GLFWwindow* window, int width, int height);
int		initGlfw(t_env *env);
int		parse(t_env *env, char *file);
int			compileShader(t_env *env);
void key(GLFWwindow *window);
void	addMat4f(char *name, t_mat4 mat, GLboolean transpose, t_env *env);
#endif
