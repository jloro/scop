/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:15:01 by jloro             #+#    #+#             */
/*   Updated: 2019/04/11 12:14:35 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XPM_H
# define XPM_H

typedef struct			s_imgInfos {
	int					width;
	int					height;
	int					nbColor;
	int					nbChar;
	unsigned char *		data;
	unsigned char **	colors;
	char **				ch;
}						t_imgInfos;

unsigned char			*loadXPM(const char * path, int * width, int * height);

#endif
