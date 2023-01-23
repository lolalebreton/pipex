/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:08:41 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/23 11:02:29 by lle-bret         ###   ########.fr       */
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

void		ft_bzero(char *s, size_t n);
int			ft_strlen(char *str);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
int			ft_strncmp(const char *s1, const char *s2, int n);
char		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strjoin(char *s1, char *s2, size_t len);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		**ft_split(char const *s, char c);
void		**ft_memfree(void **ar, int size);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
