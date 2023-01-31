/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/29 22:34:51 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fd(t_arg arg)
{
	int	j;

	j = 0;
	while (j < 2 * (arg.nb_cmd - 1))
	{
		close(arg.pipe[j]);
		++j;
	}
	if (arg.fd_in != -1)
		close(arg.fd_in);
	if (arg.fd_out != -1)
		close(arg.fd_out);
}

void	child(int i, t_arg arg, int *status)
{
	int	res;

 	arg.fd_in = arg.pipe[(2 * i - 2) * (i > 0)];
	arg.fd_out = arg.pipe[(2 * i + 1) * (i < arg.nb_cmd - 1)];
	if (i == 0)
		arg.fd_in = open(arg.file_in, O_RDONLY);
	else if (i == arg.nb_cmd - 1)
		arg.fd_out = open(arg.file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if  (arg.fd_in == -1 || arg.fd_out == -1)
		ft_exit(NULL, &arg, *status);
	printf("file in %d, file out %d\n", arg.fd_in, arg.fd_out);
	if (dup2(arg.fd_in, STDIN_FILENO) == -1
		|| dup2(arg.fd_out, STDOUT_FILENO) == -1)
		ft_exit(DUP_ERROR, &arg, *status);
	close_fd(arg);
	write(2, arg.cmd[i]->path, ft_strlen(arg.cmd[i]->path));
	write(2, "\n", 1);
	res = execve(arg.cmd[i]->path, arg.cmd[i]->option, arg.envp);
	if (res == -1)
		ft_exit(COMMAND_ERROR, &arg, COMMAND_NOT_FOUND);
}

void	pipex(t_arg arg, int *status)
{
	int		i;

	i = 0;
	while (i < arg.nb_cmd)
	{
		printf("fork %d\n", i);
		arg.pid[i] = fork();
		printf("pid : %d\n", arg.pid[i]);
		if (arg.pid[i] == -1)
			perror(NULL);
		else if (arg.pid[i] == 0)
			child(i, arg, status);
		printf("waiting for pid : %d\n", arg.pid[i]);
		waitpid(arg.pid[i], status, 0);
		printf("fork %d done\n", i);
		++i;
	}
	close_fd(arg);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
}

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;
	int		status;

	if (ac < 5)
		ft_exit(ARG_ERROR, NULL, EXIT_FAILURE);
	status = EXIT_SUCCESS;
	arg = init_arg(ac, av, envp);
	pipex(arg, &status);
	free_arg(arg);
	return (status);
}
