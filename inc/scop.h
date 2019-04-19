/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:32:44 by jloro             #+#    #+#             */
/*   Updated: 2019/04/19 15:11:31 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOPE_H
# define SCOPE_H

# include <GLFW/glfw3.h>
# include "libmat.h"

# define WIDTH_SCREEN 1000.0f
# define HEIGHT_SCREEN 1000.0f
# define F_PLANE 1000.0f
# define N_PLANE 0.1f
# define FOV 90.0f
# define MOVE_SPEED 0.25f

typedef struct		s_key
{
	int				active;
	int				key;
}					t_key;

typedef struct		s_parse
{
	GLfloat			*vertices;
	unsigned int	nbVertices;
	GLuint			*faces;
	unsigned int	nbFace;
	t_vec3			center;
	t_vec3			min;
	t_vec3			max;
}					t_parse;

typedef struct		s_key_list
{
	t_key			x;
	t_key			y;
	t_key			z;
	t_key			polygon;
	t_key			move;
	t_key			shader;
	t_key			texture;
	t_key			increase_speed;
	t_key			decrease_speed;
}					t_key_list;

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
	GLint			texLoc;
	t_parse			info;
	t_key_list		keys;
	t_vec3			rotate;
	GLuint			texture;
	float			rotate_speed;
}					t_env;


void				resize_callback(GLFWwindow* window, int width, int height);
int					initGlfw(t_env *env);
void				init_mat(t_env *env);
int					parse(t_env *env, char *file);
int					compileShader(t_env *env);
void				key(GLFWwindow *window, t_env *env);
void				init_keys(t_env *env);
#endif
