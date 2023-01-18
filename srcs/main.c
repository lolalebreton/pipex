/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:17:51 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/18 18:18:01 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	t_arg	arg;
	
	if (ac != 5)
		ft_printf("Error: wrong number of arguments were given.\n");
	else
	{
		arg.file1 = av[1];
		arg.cmd1 = av[2];
		arg.cmd2 = av[3];
		arg.file2 = av[4];
		pipex(arg);
	}
	return (0);
}