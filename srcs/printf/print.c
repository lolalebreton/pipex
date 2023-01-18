/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:50:26 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:07 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_to_print(va_list ap, t_mode *mode)
{
	char	*to_print;

	to_print = 0;
	if (ft_strchr("dDoOuUiXx", mode->conversion) && mode->precision > -1)
		mode->flag->zero = 0;
	if (ft_strchr("di", mode->conversion))
		to_print = sort_int(ap, mode);
	else if (ft_strchr("ouXx", mode->conversion))
		to_print = sort_uint(ap, mode);
	else if (ft_strchr("sc", mode->conversion))
		to_print = sort_str(ap, mode);
	else if (mode->conversion == 'p')
		to_print = sort_ptr(ap, mode);
	else if (ft_strchr("DOUCS", mode->conversion))
	{
		mode->conversion = mode->conversion + 'a' - 'A';
		mode->modifier->l = 1;
		to_print = get_to_print(ap, mode);
	}
	return (to_print);
}

int	final_print(char **to_print, t_mode *mode)
{
	int	res;

	res = 0;
	*to_print = add_precision(*to_print, mode);
	*to_print = add_alternate(*to_print, mode);
	*to_print = add_sign(*to_print, mode);
	*to_print = add_padding(*to_print, mode);
	if (!*to_print)
	{
		malloc_error();
		return (0);
	}
	res = ft_strlen(*to_print);
	if (mode->conversion == 'c' && (res < mode->width || res == 0))
	{
		if (!mode->flag->minus)
			write(1, *to_print, res);
		write(1, "\0", 1);
		if (mode->flag->minus)
			write(1, *to_print, res);
		++res;
	}
	else
		write(1, *to_print, res);
	return (res);
}
