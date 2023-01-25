/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-bret <lle-bret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:04:40 by lle-bret          #+#    #+#             */
/*   Updated: 2023/01/25 17:56:34 by lle-bret         ###   ########.fr       */
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

char	*cmd_path(char *cmd, char **paths_var)
{
	char	*res;
	int		i;

	i = 0;
	if (!cmd || access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (paths_var[i])
	{
		res = ft_strjoin(paths_var[i], cmd, ft_strlen(cmd));
		if (!res || access(res, F_OK | X_OK) == 0)
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

t_cmd	*parse_cmd(char *cmd, char **paths_var)
{
	t_cmd	*res;
	char	*slash;
	char	**split;

	res = malloc(sizeof(t_cmd));
	if (!res)
		return (NULL);
	slash = malloc(sizeof(char) * 2);
	*slash = '/';
	*(slash + 1) = 0;
	split = ft_split(cmd, ' ');
	if (!split)
		return (NULL);
	cmd = ft_strjoin(slash, split[0], ft_strlen(split[0]));
	free(slash);
	res->path = cmd_path(cmd, paths_var);
	res->option = split;
	return (res);
}
