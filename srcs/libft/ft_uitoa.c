/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:05:32 by lle-bret          #+#    #+#             */
/*   Updated: 2022/10/13 18:55:07 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uget_size(intmax_t n, intmax_t *pow, int base)
{
	int	size;

	size = 1;
	while ((unsigned long long) n >= (unsigned long long) *pow * base
		&& (unsigned long long) *pow * base > 0)
	{
		*pow *= base;
		++size;
	}
	return (size);
}

char	*ft_ufill(char *str, intmax_t n, intmax_t pow, int base)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if ((unsigned long long) n / pow < 10)
			*(str + i++) = '0' + (unsigned long long) n / pow;
		else
			*(str + i++) = 'a' + (unsigned long long) n / pow - 10;
		n = (unsigned long long) n % pow;
		pow /= base;
	}
	*(str + i) = 0;
	return (str);
}

char	*ft_uitoa(intmax_t n, int base)
{
	char		*str;
	intmax_t	pow;
	int			size;

	pow = 1;
	size = ft_uget_size((unsigned long long) n, &pow, base);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (str);
	str = ft_memset((void *) str, '0', size);
	*(str + size) = 0;
	return (ft_ufill(str, n, pow, base));
}
