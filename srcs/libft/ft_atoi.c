/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:04:50 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:55:50 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		++str;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '+') - (*str == '-');
		++str;
	}
	while (ft_isdigit(*str))
	{
		res = 10 * res + *str - '0';
		++str;
	}
	return (sign * res);
}
