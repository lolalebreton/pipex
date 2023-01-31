/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:40 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/29 22:20:28 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_arg	init_arg(int ac, char **av, char **envp)
{
	t_arg	arg;
	int		i;
	char	**path_var;

	arg.nb_cmd = ac - 3;
	arg.envp = envp;
	arg.file_in = av[1];
	arg.file_out = av[ac - 1];
	arg.fd_in = -1;
	arg.fd_out = -1;
	path_var = get_pathvar(envp);
	if (!path_var)
		ft_exit(MALLOC_ERROR, &arg, EXIT_FAILURE);
	arg.cmd = (t_cmd **) ft_calloc(sizeof(t_cmd *), arg.nb_cmd);
	if (!arg.cmd)
		ft_exit(MALLOC_ERROR, &arg, EXIT_FAILURE);
	i = 0;
	while (i < arg.nb_cmd)
	{
		arg.cmd[i] = parse_cmd(av[i + 2], path_var, &arg);
		++i;
	}
	ft_memfree((void **) path_var, -1);
	arg.pid = (pid_t *) ft_calloc(sizeof(pid_t), arg.nb_cmd - 1);
	if (!arg.pid)
		ft_exit(MALLOC_ERROR, &arg, EXIT_FAILURE);
	init_pipe(&arg);
	int j = 0;
	while (j < 2 * (arg.nb_cmd - 1))
	{
		printf("%d\n", arg.pipe[j]);
		++j;
	}
	return (arg);
}

void	init_pipe(t_arg	*arg)
{
	int	i;

	arg->pipe = (int *) ft_calloc(sizeof(int), 2 * (arg->nb_cmd - 1));
	if (!arg->pipe)
		ft_exit(MALLOC_ERROR, arg, EXIT_FAILURE);
	i = 0;
	while (i < 2 * (arg->nb_cmd - 1))
	{
		if (i % 2 == 0)
		{
			if (pipe(arg->pipe + i) == -1)
				ft_exit(PIPE_ERROR, arg, EXIT_FAILURE);
		}
		++i;
	}
}

void	ft_free(void *to_free)
{
	if (to_free)
		free(to_free);
}

void	free_arg(t_arg arg)
{
	int	i;

	i = 0;
	while (arg.cmd && i < arg.nb_cmd)
	{
		if (arg.cmd[i])
		{
			ft_free((void *) arg.cmd[i]->path);
			if (arg.cmd[i]->option)
				ft_memfree((void **) arg.cmd[i]->option, -1);
			free(arg.cmd[i]);
		}
		++i;
	}
	ft_free((void *) arg.cmd);
	ft_free((void *) arg.pid);
	i = 0;
	while (arg.pipe && i < 2 * (arg.nb_cmd - 1))
	{
		if (arg.pipe[i] && arg.pipe[i] != -1)
			close(arg.pipe[i]);
		++i;
	}
	ft_free((void *) arg.pipe);
}

void	ft_exit(char *error, t_arg *arg, int status)
{
	if (arg)
		free_arg(*arg);
	perror(error);
	exit(status);
}
