/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:50:26 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:05 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*aux_padding(char *add, char *to_print, t_mode *mode, int len)
{
	int	neg;

	neg = (ft_strchr("dDi", mode->conversion) && *to_print == '-');
	if (mode->flag->zero && !mode->flag->minus)
	{
		add = ft_memset((void *)add, '0', (size_t)(mode->width - len));
		if (neg)
		{
			*to_print = '0';
			*add = '-';
		}
	}
	else
		add = ft_memset((void *)add, ' ', (size_t)(mode->width - len));
	*(add + mode->width - len) = 0;
	if (mode->flag->minus)
		to_print = ft_append(to_print, add);
	else
		to_print = ft_prepend(to_print, add);
	return (to_print);
}

char	*add_padding(char *to_print, t_mode *mode)
{
	char	*add;
	int		len;

	if (!to_print)
		return (to_print);
	len = ft_strlen(to_print);
	add = NULL;
	if (mode->width > len)
	{
		if (mode->conversion == 'c' && *to_print == 0)
			++len;
		add = malloc(sizeof(char) * (mode->width - len + 1));
		if (!add)
		{
			free(to_print);
			return (NULL);
		}
		to_print = aux_padding(add, to_print, mode, len);
		free(add);
	}
	return (to_print);
}
