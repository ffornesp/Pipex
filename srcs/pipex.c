/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:24:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/23 18:28:47 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void	child_p(int *pip_fd, char **argv, char **envp)
{
	int		infile_fd;
	char	**cmd;
	char	*path;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		error_handle(argv[1], 1);
	close(pip_fd[0]);
	dup2(infile_fd, 0);
	dup2(pip_fd[1], 1);
	cmd = ft_split(argv[2], ' ');
	path = get_path(cmd, argv[2], envp);
	if (execve(path, cmd, envp) < 0)
		error_handle(NULL, -1);
	free(path);
	close(pip_fd[1]);
	close(infile_fd);
	return ;
}

static void	parent_p(int *pip_fd, char **argv, char **envp)
{
	int		outfile_fd;
	char	**cmd;
	char	*path;

	outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
	if (outfile_fd < 0)
		error_handle(argv[4], 2);
	close(pip_fd[1]);
	dup2(pip_fd[0], 0);
	dup2(outfile_fd, 1);
	cmd = ft_split(argv[3], ' ');
	path = get_path(cmd, argv[3], envp);
	if (execve(path, cmd, envp) < 0)
		error_handle(NULL, -1);
	free(path);
	close(pip_fd[0]);
	close(outfile_fd);
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pip_fd[2];
	int		pid;
	int		i;

	i = 0;
	if (argc != 5)
		error_handle(NULL, 0);
	while (i < argc)
	{
		if (*argv[i] == '\0' || argv[i] == NULL)
			error_handle("Invalid arguments\n", 4);
		i++;
	}
	if (pipe(pip_fd) < 0)
		error_handle(NULL, -1);
	pid = fork();
	if (pid < 0)
		error_handle(NULL, -1);
	wait(NULL);
	if (pid == 0)
		child_p(pip_fd, argv, envp);
	else
		parent_p(pip_fd, argv, envp);
	return (0);
}
