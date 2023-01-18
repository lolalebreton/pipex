/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:19:48 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 18:01:40 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *src, int n)
{
	char	*new;
	int		len_dest;
	int		len_src;
	int		i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (len_src > n)
		len_src = n;
	new = malloc(sizeof(char) * (len_dest + len_src + 1));
	if (new)
	{
		i = 0;
		while (i < len_dest + len_src)
		{
			if (i < len_dest && dest)
				*(new + i) = *(dest + i);
			else if (src)
				*(new + i) = *(src + i - len_dest);
			++i;
		}
		*(new + i) = 0;
	}
	free(dest);
	return (new);
}
