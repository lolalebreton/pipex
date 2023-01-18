/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:13:40 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/10 18:25:48 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*next_line(char *lines)
{
	size_t	i;
	size_t	j;
	char	*new_lines;

	new_lines = NULL;
	i = 0;
	j = 0;
	while (lines[i] && lines[i] != '\n')
		i++;
	if (lines[i])
	{
		new_lines = ft_calloc(((ft_strlen(lines) - i + 1)), sizeof(char));
		if (!new_lines)
			return (NULL);
		if (lines[i] == '\n')
			i++;
		while (lines[i + j])
		{
			new_lines[j] = lines[i + j];
			j++;
		}
	}
	free(lines);
	return (new_lines);
}

char	*ft_line(char *lines, char *buffer, int ret, int fd)
{
	while (ret && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buffer[ret] = '\0';
		lines = ft_strjoin(lines, buffer, ret);
		if (!lines)
			return (NULL);
	}
	return (lines);
}

char	*ft_getline(char *lines)
{
	size_t	i;
	char	*new_lines;

	i = 0;
	if (!(*lines))
		return (NULL);
	while (lines[i] && lines[i] != '\n')
		i++;
	new_lines = ft_calloc((i + 2), sizeof(char));
	if (!new_lines)
		return (NULL);
	i = 0;
	while (lines[i] && lines[i] != '\n')
	{
		new_lines[i] = lines[i];
		i++;
	}
	if (lines[i] == '\n')
		new_lines[i++] = '\n';
	new_lines[i] = 0;
	return (new_lines);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*lines;
	char		*res;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (NULL);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	lines = ft_line(lines, buffer, 1, fd);
	res = ft_getline(lines);
	lines = next_line(lines);
	free(buffer);
	return (res);
}
