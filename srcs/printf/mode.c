/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:47:49 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/09 11:58:04 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_mode(t_mode *to_free)
{
	if (to_free->modifier)
		free(to_free->modifier);
	if (to_free->flag)
		free(to_free->flag);
	free(to_free);
}

void	init_mode(t_mode *mode)
{
	mode->modifier->hh = 0;
	mode->modifier->h = 0;
	mode->modifier->ll = 0;
	mode->modifier->l = 0;
	mode->modifier->j = 0;
	mode->modifier->z = 0;
	mode->flag->sharp = 0;
	mode->flag->zero = 0;
	mode->flag->minus = 0;
	mode->flag->plus = 0;
	mode->flag->space = 0;
	mode->width = -1;
	mode->precision = -1;
	mode->conversion = 0;
	return ;
}

t_mode	*create_mode(void)
{
	t_mode		*mode;
	t_flag		*flag;
	t_modifier	*modifier;

	mode = malloc(sizeof(t_mode));
	if (!mode)
		return (NULL);
	flag = malloc(sizeof(t_flag));
	if (!flag)
	{
		free_mode(mode);
		return (NULL);
	}
	mode->flag = flag;
	modifier = malloc(sizeof(t_modifier));
	if (!modifier)
	{
		free_mode(mode);
		return (NULL);
	}
	mode->modifier = modifier;
	init_mode(mode);
	return (mode);
}
