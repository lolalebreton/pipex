/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:40 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/25 18:17:10 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_arg	init_arg(char **av, char **envp)
{
	t_arg	arg;
	char	**path_var;

	arg.envp = envp;
	arg.file1 = av[1];
	arg.file2 = av[4];
	path_var = get_pathvar(envp);
	if (!path_var)
		ft_exit(MALLOC_ERROR, &arg, EXIT_FAILURE);
	arg.cmd1 = NULL;
	arg.cmd2 = NULL;
	arg.cmd1 = parse_cmd(av[2], path_var);
	arg.cmd2 = parse_cmd(av[3], path_var);
	ft_memfree((void **) path_var, -1);
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

void	ft_exit(char *error, t_arg *arg, int status)
{
	if (arg)
		free_arg(*arg);
	perror(error);
	exit(status);
}
