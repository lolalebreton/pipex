/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/25 18:24:41 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

void	fork_in(int *pipefd, t_arg arg, int *status)
{
	int	fd;
	int	res;

	close(pipefd[0]);
	fd = open(arg.file1, O_RDONLY);
	if (fd == -1)
		ft_exit(NULL, &arg, *status);
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_exit(DUP_ERROR, &arg, *status);
	res = execve(arg.cmd1->path, arg.cmd1->option, arg.envp);
	if (res == -1)
		ft_exit(COMMAND_ERROR, &arg, COMMAND_NOT_FOUND);
}

void	fork_out(int *pipefd, t_arg arg, int *status)
{
	int	fd;
	int	res;

	fd = open(arg.file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit(NULL, &arg, *status);
	if (dup2(pipefd[0], STDIN_FILENO) == -1 || dup2(fd, STDOUT_FILENO) == -1)
		ft_exit(DUP_ERROR, &arg, *status);
	res = execve(arg.cmd2->path, arg.cmd2->option, arg.envp);
	if (res == -1)
		ft_exit(COMMAND_ERROR, &arg, COMMAND_NOT_FOUND);
}

void	pipex(t_arg arg, int *status, int *pipefd)
{
	pid_t	pid_in;
	pid_t	pid_out;

	pid_in = fork();
	if (pid_in == -1)
		perror(NULL);
	else if (pid_in == 0)
		fork_in(pipefd, arg, status);
	close(pipefd[1]);
	pid_out = fork();
	if (pid_out == -1)
		perror(NULL);
	else if (pid_out == 0)
		fork_out(pipefd, arg, status);
	close(pipefd[0]);
	waitpid(pid_in, status, 0);
	waitpid(pid_out, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
}

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;
	int		status;
	int		pipefd[2];

	if (ac != 5)
		ft_exit(ARG_ERROR, NULL, EXIT_FAILURE);
	status = EXIT_SUCCESS;
	arg = init_arg(av, envp);
	if (!arg.cmd1 || !arg.cmd2)
		ft_exit(MALLOC_ERROR, &arg, status);
	if (pipe(pipefd) == -1)
		ft_exit(PIPE_ERROR, &arg, status);
	pipex(arg, &status, pipefd);
	free_arg(arg);
	return (status);
}
