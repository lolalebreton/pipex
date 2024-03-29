/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:18:25 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/31 14:53:34 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define ARG_ERROR "Error: Wrong number of arguments (expected 4)"
# define PIPE_ERROR "Pipe error"
# define MALLOC_ERROR "Malloc error"
# define FILE_ERROR "File error"
# define DUP_ERROR "Dup2 error"
# define COMMAND_ERROR "Command not found"
# define COMMAND_NOT_FOUND 127

typedef struct s_cmd {
	char	*path;
	char	**option;
}	t_cmd;

typedef struct s_arg {
	char	*file_in;
	char	*file_out;
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	char	**envp;
}	t_arg;

/* ************************************************************************** */
/*                                  pipex.c                                   */
/* ************************************************************************** */

void	fork_in(int *pipefd, t_arg arg, int *status);
void	fork_out(int *pipefd, t_arg arg, int *status);
void	pipex(t_arg arg, int *status, int *pipefd);

/* ************************************************************************** */
/*                                 command.c                                  */
/* ************************************************************************** */

char	**get_pathvar(char **env);
char	*cmd_path(char *cmd, char **paths_var, t_arg *arg);
t_cmd	*parse_cmd(char *cmd, char **paths_var, t_arg *arg);

/* ************************************************************************** */
/*                                   utils.c                                  */
/* ************************************************************************** */

t_arg	init_arg(char **av, char **envp);
void	init_pipe(t_arg	*arg);
void	ft_free(void *to_free);
void	free_arg(t_arg arg);
void	ft_exit(char *error, t_arg *arg, int status);

#endif