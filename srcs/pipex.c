/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/20 17:59:20 by lle-bret         ###   ########.fr       */
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
	res = execve(cmd.path, cmd.argv, env);
	if (res == -1)
	{
		perror(NULL);
		ft_exit("Execve error");
	}
}

void	pipex(t_arg arg, int *status)
{
	pid_t	pid;
	int		*pipefd;
	int		file1;
	int		file2;

	*status = 42;
	pipefd = create_pipe();
	pid = fork();
	if (pid == -1)
		perror(NULL);
	else if (pid == 0)
	{
		close(pipefd[0]);
		file1 = open(arg.file1, O_RDONLY);
		if (file1 == -1)
			ft_exit("File error");
		execute_cmd(arg.cmd1, file1, pipefd[1], arg.envp);
	}
	waitpid(pid, status, 0);
	close(pipefd[1]);
	file2 = open(arg.file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file2 == -1)
		ft_exit("File error");
	execute_cmd(arg.cmd2, pipefd[0], file2, arg.envp);
}

int	main(int ac, char **av, char **envp)
{
	t_arg	arg;
	int		status;
	char	**path_var;
	char	*path;

	if (ac != 5)
		ft_exit("Error: wrong number of arguments were given.\n");
	arg.envp = envp;
	arg.file1 = av[1];
	path_var = get_pathvar(envp);
	arg.cmd1 = parse_cmd(av[2]);
	path = cmd_path(arg.cmd1.path, path_var);
	if (!path)
		ft_exit(MALLOC_ERROR);
	arg.cmd1.path = path;
	arg.cmd2 = parse_cmd(av[3]);
	path = cmd_path(arg.cmd2.path, path_var);
	if (!path)
		ft_exit(MALLOC_ERROR);
	arg.cmd2.path = path;
	arg.file2 = av[4];
	pipex(arg, &status);
	return (0);
}
