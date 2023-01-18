/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:08:41 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/18 16:49:44 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

// LIBFT

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(char *s, size_t n);
int			ft_strlen(char *str);
int			ft_toupper(int c);
int			ft_isdigit(int c);
char		*ft_strchr(const char *s, int c);
int			ft_atoi(const char *str);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_itoa(intmax_t n, int base);
char		*ft_uitoa(intmax_t n, int base);
char		*ft_strtoupper(char *str);
void		*ft_memalloc(size_t size);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strncat(char *dest, char *src, int n);
char		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char *s1, char *s2, size_t len);
void		*ft_memcpy(void *dest, const void *src, size_t n);

// GET NEXT LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

char	*get_next_line(int fd);

// PRINTF

typedef struct s_flag {
	int	sharp;
	int	zero;
	int	minus;
	int	plus;
	int	space;
}	t_flag;

typedef struct s_modifier {
	int	hh;
	int	h;
	int	ll;
	int	l;
	int	j;
	int	z;
}	t_modifier;

typedef struct s_mode {
	t_flag		*flag;
	t_modifier	*modifier;
	int			width;
	int			precision;
	char		conversion;
}	t_mode;

int			ft_printf(const char *format, ...);

// Mode
t_mode		*create_mode(void);
void		init_mode(t_mode *mode);
void		free_mode(t_mode *mode);

// Util
void		*malloc_error(void);
char		*ft_prepend(char *to_print, char *to_add);
char		*ft_append(char *to_print, char *to_add);

// Parse
const char	*get_flag(const char *format, t_mode *mode);
const char	*get_width(const char *format, t_mode *mode);
const char	*get_precision(const char *format, t_mode *mode);
const char	*get_modifier(const char *format, t_mode *mode);

// Convert
char		*convert_int(intmax_t n, t_mode *mode);
char		*convert_str(char *str, t_mode *mode);
char		*convert_char(char c);

// Sort
char		*sort_int(va_list ap, t_mode *mode);
char		*sort_uint(va_list ap, t_mode *mode);
char		*sort_str(va_list ap, t_mode *mode);
char		*sort_ptr(va_list ap, t_mode *mode);

// Print
char		*get_to_print(va_list ap, t_mode *mode);
int			final_print(char **to_print, t_mode *mode);

// Flags
char		*add_alternate(char *to_print, t_mode *mode);
char		*add_sign(char *to_print, t_mode *mode);
char		*add_precision(char *to_print, t_mode *mode);

// Padding
char		*add_padding(char *to_print, t_mode *mode);

#endif
