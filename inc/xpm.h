/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:15:01 by jloro             #+#    #+#             */
/*   Updated: 2019/04/19 16:11:11 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_H
# define XPM_H

typedef struct			s_img_infos {
	int					width;
	int					height;
	int					nb_color;
	int					nb_char;
	unsigned char		*data;
	unsigned char		**colors;
	char				**ch;
}						t_img_infos;

unsigned char			*loadxpm(const char *path, int *width, int *height);

#endif
