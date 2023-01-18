/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:50:26 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:14 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_alternate(char *to_print, t_mode *mode)
{
	if (!to_print)
		return (to_print);
	if (mode->flag->sharp)
	{
		if (mode->conversion == 'o' && *to_print != '0')
		{
			to_print = ft_prepend(to_print, "0");
		}
		else if ((mode->conversion == 'x' && *to_print != '0')
			|| mode->conversion == 'p')
		{
			to_print = ft_prepend(to_print, "0x");
		}
		else if (mode->conversion == 'X' && *to_print != '0')
			to_print = ft_prepend(to_print, "0X");
	}
	return (to_print);
}

char	*add_sign(char *to_print, t_mode *mode)
{
	if (!to_print)
		return (to_print);
	if (mode->flag->plus && ft_strchr("diD", mode->conversion)
		&& *to_print != '-')
		to_print = ft_prepend(to_print, "+");
	if (!to_print)
		return ((char *) malloc_error());
	if (mode->flag->space && ft_strchr("diD", mode->conversion)
		&& *to_print != '-')
		to_print = ft_prepend(to_print, " ");
	return (to_print);
}

char	*add_precision(char *to_print, t_mode *mode)
{
	char	*add;
	int		len;
	int		neg;

	len = ft_strlen(to_print);
	neg = (ft_strchr("dDi", mode->conversion) && *to_print == '-');
	if (ft_strchr("diouxX", mode->conversion) && len - neg < mode->precision)
	{
		len -= neg;
		add = malloc(sizeof(char) * (mode->precision - len + 1));
		if (!add)
			return ((char *) malloc_error());
		add = ft_memset(add, 48, (size_t) mode->precision - len);
		*(add + mode->precision - len) = 0;
		if (neg)
		{
			*to_print = '0';
			*add = '-';
		}
		to_print = ft_prepend(to_print, add);
		free(add);
	}
	return (to_print);
}
