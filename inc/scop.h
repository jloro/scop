/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:32:44 by jloro             #+#    #+#             */
/*   Updated: 2019/04/16 16:56:10 by jloro            ###   ########.fr       */
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
# define MOVE_SPEED 0.05f

typedef struct	s_env
{
	GLFWwindow	*window;
	GLuint		shaderProgram;
	GLuint		VAO;
	GLuint		VBO;
	GLuint		EBO;
	t_mat4		vp;
	t_mat4		model;
	GLint		vpLoc;
	GLint		modelLoc;
	GLint		transformLoc;
	unsigned int	nbFace;
	int			polygon;
	t_mat4		trans;
}				t_env;

typedef struct	s_parse
{
	float			*vertex;
	unsigned int	nbVertex;
	unsigned int	*faces;
	unsigned int	nbFace;
}				t_parse;


void	resize_callback(GLFWwindow* window, int width, int height);
int		initGlfw(t_env *env);
void		init_mat(t_env *env);
int		parse(t_env *env, char *file);
int			compileShader(t_env *env);
void key(GLFWwindow *window, t_env *env);
#endif
