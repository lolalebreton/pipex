/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:34:33 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/18 18:35:30 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_cmd(char *file)
{
	pid_t	pid;
	int	status;

	status = -1;
	pid = fork();
	if (pid == -1)
		perror(NULL);
	else if (pid == 0)
		execve(file, NULL, NULL);
	else if (pid > 0)
		wait(&status);
	return (status);
}

int	execute_cmd(t_arg arg)
{
	int	fd;
	int	status;

	fd = open("cmd.sh", O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
	{
		perror(NULL);
		unlink("cmd.sh");
		return (0);
	}
	if (write(fd, "#!/bin/bash\n", 12) == -1
		|| write(fd, "< ", 2) == -1
		|| write(fd, arg.file1, ft_strlen(arg.file1)) == -1
		|| write(fd, " ", 1) == -1
		|| write(fd, arg.cmd1, ft_strlen(arg.cmd1)) == -1
		|| write(fd, " | ", 3) == -1
		|| write(fd, arg.cmd2, ft_strlen(arg.cmd2)) == -1
		|| write(fd, " > ", 3) == -1 
		|| write(fd, arg.file2, ft_strlen(arg.file2)) == -1)
	{
		perror(NULL);
		unlink("cmd.sh");
		return (0);
	}
	close(fd);
	status = fork_cmd("cmd.sh");
	if (status == -1 || unlink("cmd.sh") == -1)
	{
		perror(NULL);
		return (0);
	}
	return (1);
}


void	pipex(t_arg arg)
{
	execute_cmd(arg);
}
