/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:05:32 by lle-bret          #+#    #+#             */
/*   Updated: 2022/10/12 17:11:11 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_size(intmax_t n, intmax_t *pow, int base)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		++size;
		n *= -1;
	}
	while (n >= *pow * base && *pow * base > 0)
	{
		*pow *= base;
		++size;
	}
	return (size);
}

char	*ft_fill(char *str, intmax_t n, intmax_t pow, int base)
{
	int	i;
	int	neg;

	i = 0;
	neg = (n < 0);
	if (neg)
	{
		n *= -1;
		*(str + i++) = '-';
	}
	while (*(str + i))
	{
		if (n / pow < 10)
			*(str + i++) = '0' + n / pow;
		else
			*(str + i++) = 'a' + n / pow - 10;
		n = n % pow;
		pow /= base;
	}
	*(str + i) = 0;
	return (str);
}

char	*ft_itoa(intmax_t n, int base)
{
	char		*str;
	intmax_t	pow;
	int			size;

	pow = 1;
	size = ft_get_size(n, &pow, base);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (str);
	str = ft_memset((void *) str, '0', size);
	*(str + size) = 0;
	return (ft_fill(str, n, pow, base));
}
