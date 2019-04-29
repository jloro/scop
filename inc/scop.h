/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:32:44 by jloro             #+#    #+#             */
/*   Updated: 2019/04/29 17:19:56 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <GLFW/glfw3.h>
# include "libmat.h"

# define WIDTH_SCREEN 1000.0f
# define HEIGHT_SCREEN 1000.0f
# define F_PLANE 100000.0f
# define N_PLANE 0.1f
# define FOV 90.0f

typedef struct		s_key
{
	int				active;
	int				key;
}					t_key;

typedef struct		s_parse
{
	GLfloat			*vertices;
	unsigned int	nb_vertices;
	GLuint			*faces;
	unsigned int	nb_face;
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
	t_key			increase_rot_speed;
	t_key			decrease_rot_speed;
	t_key			increase_move_speed;
	t_key			decrease_move_speed;
	t_key			flat;
}					t_key_list;

typedef struct		s_env
{
	GLFWwindow		*window;
	GLuint			shader_program;
	GLuint			vao;
	GLuint			vbo;
	GLuint			ebo;
	t_mat4			vp;
	t_mat4			model;
	GLint			vp_loc;
	GLint			model_loc;
	GLint			transform_loc;
	GLint			tex_loc;
	GLint			flat_loc;
	t_parse			info;
	t_key_list		keys;
	t_vec3			rotate;
	GLuint			texture;
	float			rotate_speed;
	float			move_speed;
}					t_env;

void				resize_callback(GLFWwindow *window, int width, int height);
int					init(t_env *env);
void				init_mat(t_env *env);
int					parse(t_env *env, char *file);
int					compile_shader(t_env *env);
void				key(GLFWwindow *window, t_env *env);
void				init_keys(t_env *env);
int					send_opengl(t_parse *info, t_env *env);

#endif
