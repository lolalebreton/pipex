/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:19:48 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/12 15:26:53 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*buff;

	buff = malloc(size * nmemb);
	if (!buff)
		return (NULL);
	ft_bzero(buff, (size * nmemb));
	return (buff);
}
