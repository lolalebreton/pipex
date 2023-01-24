/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/24 16:33:45 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

int	*create_pipe(t_arg arg)
{
	int	*pipefd;

	pipefd = malloc(sizeof(int) * 2);
	if (!pipefd || pipe(pipefd) == -1)
	{
		perror(NULL);
		ft_exit(PIPE_ERROR, &arg, pipefd);
	}
	return (pipefd);
}

void	fork_in(int *pipefd, t_arg arg)
{
	int	fd;
	int	res;

	close(pipefd[0]);
	fd = open(arg.file1, O_RDONLY);
	if (fd == -1)
		ft_exit(NULL, &arg, pipefd);
	if (dup2(fd, STDIN_FILENO) == -1 || dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_exit(DUP_ERROR, &arg, pipefd);
	res = execve(arg.cmd1->path, arg.cmd1->option, arg.envp);
	if (res == -1)
		ft_exit(EXECVE_ERROR, &arg, pipefd);
}

void	fork_out(int *pipefd, t_arg arg)
{
	int	fd;
	int	res;

	fd = open(arg.file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit(NULL, &arg, pipefd);
	if (dup2(pipefd[0], STDIN_FILENO) == -1 || dup2(fd, STDOUT_FILENO) == -1)
		ft_exit(DUP_ERROR, &arg, pipefd);
	res = execve(arg.cmd2->path, arg.cmd2->option, arg.envp);
	if (res == -1)
		ft_exit(EXECVE_ERROR, &arg, pipefd);
}

void	pipex(t_arg arg, int *status, int *pipefd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror(NULL);
	else if (pid == 0)
		fork_in(pipefd, arg);
	waitpid(pid, status, 0);
	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
		perror(NULL);
	else if (pid == 0)
		fork_out(pipefd, arg);
	waitpid(pid, status, 0);
	close(pipefd[0]);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else
		*status = EXIT_FAILURE;
}

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;
	int		status;
	int		*pipefd;

	if (ac != 5)
		ft_exit("Error: Wrong number of arguments (expected 4)", NULL, NULL);
	status = EXIT_SUCCESS;
	arg = init_arg(av, envp);
	pipefd = create_pipe(arg);
	if (arg.cmd1 && arg.cmd2 && pipefd)
		pipex(arg, &status, pipefd);
	else
		status = EXIT_FAILURE;
	free_arg(arg);
	if (pipefd)
		free(pipefd);
	return (status);
}
