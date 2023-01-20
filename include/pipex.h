/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:18:25 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/20 17:43:57 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define PIPE_ERROR "Pipe error"
# define MALLOC_ERROR "Malloc error"

typedef struct s_cmd {
	char	*path;
	char	**argv;
}	t_cmd;
typedef struct s_arg {
	char	*file1;
	char	*file2;
	t_cmd	cmd1;
	t_cmd	cmd2;
	char	**envp;
}	t_arg;

/* ************************************************************************** */
/*                                  pipex.c                                   */
/* ************************************************************************** */

int		*create_pipe(void);
void	execute_cmd(t_cmd cmd, int in, int out, char **env);
t_cmd	parse_cmd(char *cmd);
void	pipex(t_arg arg, int *status);

/* ************************************************************************** */
/*                                   utils.c                                  */
/* ************************************************************************** */

char	**get_pathvar(char **env);
char	*cmd_path(char *cmd, char **env_paths);
void	ft_exit(char *error);

#endif