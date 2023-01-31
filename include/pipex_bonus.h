/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:18:25 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/29 22:21:24 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

# define ARG_ERROR "Error: Wrong number of arguments (expected at least 4)"
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
	int		fd_in;
	int		fd_out;
	int		nb_cmd;
	t_cmd	**cmd;
	pid_t	*pid;
	char	**envp;
	int		*pipe;
}	t_arg;

/* ************************************************************************** */
/*                                  pipex.c                                   */
/* ************************************************************************** */

void	child(int i, t_arg arg, int *status);
void	pipex(t_arg arg, int *status);

/* ************************************************************************** */
/*                                 command.c                                  */
/* ************************************************************************** */

char	**get_pathvar(char **env);
char	*cmd_path(char *cmd, char **paths_var, t_arg *arg);
t_cmd	*parse_cmd(char *cmd, char **paths_var, t_arg *arg);

/* ************************************************************************** */
/*                                   utils.c                                  */
/* ************************************************************************** */

void	init_pipe(t_arg	*arg);
t_arg	init_arg(int ac, char **av, char **envp);
void	free_arg(t_arg arg);
void	ft_exit(char *error, t_arg *arg, int status);

#endif