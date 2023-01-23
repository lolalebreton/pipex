/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:40 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/23 14:01:00 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_arg	init_arg(char **av, char **envp)
{
	t_arg	arg;

	arg.envp = envp;
	arg.file1 = av[1];
	arg.file2 = av[4];
	arg.cmd1 = NULL;
	arg.cmd2 = NULL;
	return (arg);
}

void	free_arg(t_arg arg)
{
	if (arg.cmd1)
	{
		if (arg.cmd1->path)
			free(arg.cmd1->path);
		if (arg.cmd1->option)
			ft_memfree((void **) arg.cmd1->option, -1);
		free(arg.cmd1);
	}
	if (arg.cmd2)
	{
		if (arg.cmd2->path)
			free(arg.cmd2->path);
		if (arg.cmd2->option)
			ft_memfree((void **) arg.cmd2->option, -1);
		free(arg.cmd2);
	}
}

void	ft_exit(char *error)
{
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	//perror(error);
	exit(EXIT_FAILURE);
}
