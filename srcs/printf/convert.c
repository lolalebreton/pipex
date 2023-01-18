/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:50:26 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:13 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*convert_int(intmax_t n, t_mode *mode)
{
	char	*nb;

	if (ft_strchr("oO", mode->conversion))
		nb = ft_itoa(n, 8);
	else if (ft_strchr("Ddi", mode->conversion))
		nb = ft_itoa(n, 10);
	else if (ft_strchr("uU", mode->conversion))
		nb = ft_uitoa(n, 10);
	else if (mode->conversion == 'x' || mode->conversion == 'p')
		nb = ft_uitoa(n, 16);
	else if (mode->conversion == 'X')
		nb = ft_strtoupper(ft_uitoa(n, 16));
	else
		return (NULL);
	if (!nb)
		return ((char *) malloc_error());
	return (nb);
}

char	*convert_str(char *str, t_mode *mode)
{
	char	*to_print;
	int		len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (mode->precision > -1 && mode->precision < len)
		len = mode->precision;
	to_print = ft_memalloc(sizeof(char) * (len + 1));
	if (!to_print)
	{
		malloc_error();
		return (to_print);
	}
	to_print = ft_strncpy(to_print, str, len);
	return (to_print);
}

char	*convert_char(char c)
{
	char	*to_print;

	to_print = ft_memalloc(sizeof(char) * 2);
	if (!to_print)
		return (to_print);
	*to_print = c;
	*(to_print + 1) = 0;
	return (to_print);
}
