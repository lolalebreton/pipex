/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:07:22 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/23 11:02:41 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start >= (unsigned int) ft_strlen((char *) s))
		len = 0;
	else if ((size_t) ft_strlen((char *)(s + start)) < len)
		len = ft_strlen((char *)(s + start));
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (sub);
	i = 0;
	while (i < len)
	{
		*(sub + i) = *(s + start + i);
		++i;
	}
	*(sub + i) = 0;
	return (sub);
}
