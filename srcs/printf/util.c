/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:47:49 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:10 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*malloc_error(void)
{
	write(1, "Malloc Error: program failed\n", 29);
	return (0);
}

char	*ft_prepend(char *str, char *add)
{
	char	*new;
	int		len;

	if (!add || *add == 0)
		return (str);
	len = ft_strlen(add);
	new = malloc(sizeof(char) * (len + ft_strlen(str) + 1));
	if (!new)
		return (new);
	new = ft_strcpy(new, add);
	ft_strcpy(new + len, str);
	free(str);
	return (new);
}

char	*ft_append(char *str, char *add)
{
	char	*new;
	int		len;

	if (!add || *add == 0)
		return (str);
	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + ft_strlen(add) + 1));
	if (!new)
		return (new);
	new = ft_strcpy(new, str);
	ft_strcpy(new + len, add);
	free(str);
	return (new);
}
