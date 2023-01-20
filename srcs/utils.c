/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:40 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/20 17:59:43 by lle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_pathvar(char **env)
{
	int		i;
	char	**res;

	i = 0;
	while (ft_strncmp(env[i], "PATH", 4) != 0)
	{
		++i;
	}
	res = ft_split(env[i], '=');
	if (!res)
		return (NULL);
	res = ft_split(res[1], ':');
	return (res);
}

char	*cmd_path(char *cmd, char **paths_var)
{
	char	*res;
	int		i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (paths_var[i])
	{
		res = ft_strjoin(paths_var[i], cmd, ft_strlen(cmd));
		if (!res)
			return (NULL);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		++i;
	}
	return (res);
}

t_cmd	parse_cmd(char *cmd)
{
	t_cmd	res;
	char	*slash;
	char	**split;

	slash = malloc(sizeof(char) * 2);
	*slash = '/';
	*(slash + 1) = 0;
	split = ft_split(cmd, ' ');
	res.path = ft_strjoin(slash, split[0], ft_strlen(split[0]));
	res.argv = split;
	return (res);
}

void	ft_exit(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
