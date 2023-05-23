/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:39:57 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/23 19:11:33 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

static char	*get_cmd_path(char **path)
{
	int		i;
	char	*out;

	i = 0;
	out = NULL;
	while (path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
			out = ft_strdup(path[i]);
		free(path[i]);
		i++;
	}
	free(path);
	if (out)
		return (out);
	return (NULL);
}

static char	**join_path_cmd(char **path, char **cmd)
{
	int		i;
	char	*aux;

	i = 0;
	while (path[i])
	{
		aux = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(aux);
		aux = path[i];
		path[i] = ft_strjoin(path[i], cmd[0]);
		free(aux);
		i++;
	}
	return (path);
}

char	*get_path(char **cmd, char *line_cmd, char **envp)
{
	int		i;
	char	**path;
	char	*aux;
	char	*out;

	i = 0;
	while (envp[i])
	{
		aux = ft_strnstr(envp[i], "PATH", 4);
		if (aux != NULL)
			break;
		i++;
	}
	if (!aux)
		error_handle(line_cmd, 5);
	aux = ft_strtrim(aux, "PATH=");
	path = ft_split(aux, ':');
	free(aux);
	out = NULL;
	path = join_path_cmd(path, cmd);
	out = get_cmd_path(path);
	if (!out)
		error_handle(line_cmd, 3);
	return (out);
}
