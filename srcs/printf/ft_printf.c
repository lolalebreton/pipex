/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:50:26 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:02 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*parse_format(const char *format, va_list ap, t_mode *mode,
		int *res)
{
	char	*to_print;

	format = get_flag(format, mode);
	format = get_width(format, mode);
	format = get_precision(format, mode);
	format = get_modifier(format, mode);
	if (*format && ft_strchr("dDoOuUiXxsSpcC", *format))
	{
		mode->conversion = *(format++);
		to_print = get_to_print(ap, mode);
		if (to_print)
		{
			*res += final_print(&to_print, mode);
			free(to_print);
		}
		else
			return ((const char *) malloc_error());
	}
	return (format);
}

const char	*print_format(const char *format, va_list ap, int *res)
{
	t_mode	*mode;

	if (!ft_strchr("0123456789 +-#sSpdDioOuUxXcC.hhljz", *format))
	{
		++*res;
		write(1, format++, 1);
		return (format);
	}
	mode = create_mode();
	if (!mode)
	{
		malloc_error();
		return (NULL);
	}
	format = parse_format(format, ap, mode, res);
	free_mode(mode);
	return (format);
}

int	get_res(va_list ap, const char *format)
{
	int	res;

	res = 0;
	while (format && *format)
	{
		if (*format == '%')
		{
			++format;
			if (*format == '%')
			{
				++res;
				write(1, "%", 1);
				++format;
			}
			else if (*format)
				format = print_format(format, ap, &res);
		}
		else
		{
			++res;
			write(1, format++, 1);
		}
	}
	return (res);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = get_res(ap, format);
	va_end(ap);
	return (res);
}
