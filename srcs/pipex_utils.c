/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:34:02 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/25 15:00:08 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>

void	exec_cmd(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = get_path(cmd, argv, envp);
	if (execve(path, cmd, envp))
		error_handle(NULL, -1);
	free(path);
}

void	dup_and_close(int fd_1, int fd_2)
{
	if (dup2(fd_1, 0) < 0)
		error_handle(NULL, -1);
	close(fd_1);
	if (dup2(fd_2, 1) < 0)
		error_handle(NULL, -1);
	close(fd_2);
}
