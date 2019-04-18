/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:32:44 by jloro             #+#    #+#             */
/*   Updated: 2019/04/18 16:27:22 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPE_H
# define SCOPE_H

# include <GLFW/glfw3.h>
# include "libmat.h"

# define WIDTH_SCREEN 800.0f
# define HEIGHT_SCREEN 600.0f
# define F_PLANE 1000.0f
# define N_PLANE 0.1f
# define FOV 90.0f
# define MOVE_SPEED 0.25f

typedef struct		s_key
{
	int				active;
	int				key;
}					t_key;

typedef struct		s_env
{
	GLFWwindow		*window;
	GLuint			shaderProgram;
	GLuint			VAO;
	GLuint			VBO;
	GLuint			EBO;
	t_mat4			vp;
	t_mat4			model;
	GLint			vpLoc;
	GLint			modelLoc;
	GLint			transformLoc;
	unsigned int	nbFace;
	t_key			polygon;
	t_key			move;
	t_key			shader;
	//aled jpeu pas lenlever V
	t_mat4			t;
}					t_env;

typedef struct		s_parse
{
	GLfloat			*vertices;
	unsigned int	nbVertices;
	GLuint			*faces;
	unsigned int	nbFace;
	GLfloat			max;
	GLfloat			min;
}					t_parse;


void				resize_callback(GLFWwindow* window, int width, int height);
int					initGlfw(t_env *env);
void				init_mat(t_env *env);
int					parse(t_env *env, char *file);
int					compileShader(t_env *env);
void				key(GLFWwindow *window, t_env *env);
#endif
