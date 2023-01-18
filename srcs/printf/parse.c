/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:50:26 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:06 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*get_flag(const char *format, t_mode *mode)
{
	while (*format && ft_strchr("#0-+ ", *format))
	{
		if (*format == '#')
			mode->flag->sharp = 1;
		else if (*format == '0')
			mode->flag->zero = 1;
		else if (*format == '-')
			mode->flag->minus = 1;
		else if (*format == '+')
			mode->flag->plus = 1;
		else if (*format == ' ')
			mode->flag->space = 1;
		++format;
	}
	return (format);
}

const char	*get_width(const char *format, t_mode *mode)
{
	if (*format && ft_strchr("0123456789", *format))
	{
		mode->width = ft_atoi(format);
		while (ft_strchr("0123456789", *format))
			++format;
	}
	return (format);
}

const char	*get_precision(const char *format, t_mode *mode)
{
	if (*format == '.')
	{
		++format;
		mode->precision = ft_atoi(format);
		while (ft_strchr("0123456789", *format))
			++format;
	}
	return (format);
}

const char	*get_modifier(const char *format, t_mode *mode)
{	
	while (*format && ft_strchr("hljz", *format))
	{
		if (*format == 'j')
			mode->modifier->j = 1;
		else if (*format == 'z')
			mode->modifier->z = 1;
		else if (*format == 'h')
		{
			if (*(format + 1) == 'h')
				mode->modifier->hh = 1;
			else
				mode->modifier->h = 1;
		}
		else if (*format == 'l')
		{
			if (*(format + 1) == 'l')
				mode->modifier->ll = 1;
			else
				mode->modifier->l = 1;
		}
		++format;
	}
	return (format);
}
