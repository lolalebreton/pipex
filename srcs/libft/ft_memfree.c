/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:06:10 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/23 13:57:45 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_memfree(void **ar, int size)
{
	while (size > 0)
	{
		free(ar[size - 1]);
		--size;
	}
	if (size == -1)
	{
		++size;
		while (ar[size])
		{
			free(ar[size]);
			++size;
		}
	}
	free(ar);
	return (NULL);
}
