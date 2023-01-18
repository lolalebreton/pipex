/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:07:01 by lle-bret          #+#    #+#             */
/*   Updated: 2022/09/25 20:07:02 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && *(src + i))
	{
		*(dst + i) = *(src + i);
		++i;
	}
	while (i < len)
	{
		*(dst + i) = 0;
		++i;
	}
	return (dst);
}
