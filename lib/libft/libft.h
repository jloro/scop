/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:47:42 by jloro             #+#    #+#             */
/*   Updated: 2018/01/13 05:00:25 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include "stdio.h"
# include "string.h"
# include "ctype.h"
# include "unistd.h"
# include "includes/get_next_line.h"

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	int				fd;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack,
		const char *needle, size_t len);
char				*ft_strncpy(char *dest, const char *src, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnew(size_t size);
void				*ft_memalloc(size_t size);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strmap(char const *s, char (*f)(char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strtrim(char const *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_compte_c(char *s, char c);
void				ft_lstaddend(t_list **begin, t_list *end);
int					ft_ischr(const char *s, char c);
int					ft_indice_c(const char *s, char c);
char				*ft_strcpyc(char *dest, const char *src, int c);
int					ft_2compte_c(char **tab, char c);
int					ft_ischrcol(char **tab, int j, char c);
void				ft_2print(char **tab, int bn);
int					ft_nbline(char **tab);
void				ft_2tabdel(void **tab, int len);
char				*ft_itoa_base(int nb, int base);
int					ft_power(int nb, int power);
int					ft_itoa_dec(char *nbr, int base);
#endif
