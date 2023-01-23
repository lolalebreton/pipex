/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/23 14:03:05 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>

int	*create_pipe(void)
{
	int	*pipefd;

	pipefd = malloc(sizeof(int) * 2);
	if (pipe(pipefd) == -1)
	{
		perror(NULL);
		ft_exit(PIPE_ERROR);
	}
	return (pipefd);
}

void	execute_cmd(t_cmd cmd, int filein, int fileout, char **env)
{
	int	res;

	if (dup2(filein, STDIN_FILENO) == -1 || dup2(fileout, STDOUT_FILENO) == -1)
		ft_exit("Dup2 error");
	res = execve(cmd.path, cmd.option, env);
	if (res == -1)
	{
		perror(NULL);
		ft_exit("Execve error");
	}
}

void	ft_fork1(int* pipefd, t_arg arg)
{
	int	fd;
	
	close(pipefd[0]);
	fd = open(arg.file1, O_RDONLY);
	if (fd == -1)
		ft_exit("File error");
	execute_cmd(*arg.cmd1, fd, pipefd[1], arg.envp);
}

void	ft_fork2(int* pipefd, t_arg arg)
{
	int	fd;
	
	fd = open(arg.file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit("File error");
	execute_cmd(*arg.cmd2, pipefd[0], fd, arg.envp);
}

int	pipex(t_arg arg, int *status, int *pipefd)
{
	pid_t	pid;

	*status = 42;
	pid = fork();
	if (pid == -1)
		perror(NULL);
	else if (pid == 0)
		ft_fork1(pipefd, arg);
	waitpid(pid, status, 0);
	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
		perror(NULL);
	else if (pid == 0)
		ft_fork2(pipefd, arg);
	waitpid(pid, status, 0);
	close(pipefd[0]);
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	return (EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;
	int		status;
	char	**path_var;
	int		*pipefd;

	if (ac != 5)
		ft_exit("Error: wrong number of arguments were given.\n");
	status = 0;
	arg = init_arg(av, envp);
	path_var = get_pathvar(envp);
	if (!path_var)
		ft_exit(MALLOC_ERROR);
	arg.cmd1 = parse_cmd(av[2], path_var);
	arg.cmd2 = parse_cmd(av[3], path_var);
	pipefd = create_pipe();
	if (arg.cmd1 && arg.cmd2 && pipefd)
		status = pipex(arg, &status, pipefd);
	free_arg(arg);
	ft_memfree((void **) path_var, -1);
	if (pipefd)
		free(pipefd);
	return (status);
}

//WIFEXITED
//WEXITSTATUS