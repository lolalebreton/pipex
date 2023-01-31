/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:40 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/29 21:32:18 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_pathvar(char **env)
{
	int		i;
	char	**tmp;
	char	**res;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
		++i;
	tmp = ft_split(env[i], '=');
	if (!tmp || !tmp[0] || !tmp[1])
	{
		ft_memfree((void **) tmp, -1);
		return (NULL);
	}
	res = ft_split(tmp[1], ':');
	ft_memfree((void **) tmp, -1);
	return (res);
}

char	*cmd_path(char *cmd, char **paths_var, t_arg *arg)
{
	char	*res;
	int		i;

	i = 0;
	if (!cmd || access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (paths_var[i])
	{
		res = ft_strjoin(paths_var[i], cmd, ft_strlen(cmd));
		if (!res)
		{
			free(cmd);
			ft_exit(MALLOC_ERROR, arg, EXIT_FAILURE);
		}
		if (access(res, F_OK | X_OK) == 0)
		{
			free(cmd);
			return (res);
		}
		free(res);
		++i;
	}
	free(cmd);
	return (NULL);
}

t_cmd	*parse_cmd(char *cmd, char **paths_var, t_arg *arg)
{
	t_cmd	*res;
	char	**split;

	res = malloc(sizeof(t_cmd));
	if (!res)
		ft_exit(MALLOC_ERROR, arg, EXIT_FAILURE);
	split = ft_split(cmd, ' ');
	if (!split)
	{
		free(res);
		ft_exit(MALLOC_ERROR, arg, EXIT_FAILURE);
	}
	cmd = ft_strjoin("/", split[0], ft_strlen(split[0]));
	if (!cmd)
	{
		free(split);
		free(res);
		ft_exit(MALLOC_ERROR, arg, EXIT_FAILURE);
	}
	res->path = cmd_path(cmd, paths_var, arg);
	res->option = split;
	return (res);
}
