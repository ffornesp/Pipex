/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:24:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/24 14:26:46 by ffornes-         ###   ########.fr       */
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

static void	init_p(int *pip_fd, char **argv, char **envp)
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
}

static void	finish_p(int *pip_fd, int i, char **argv, char **envp)
{
	int		outfile_fd;
	char	**cmd;
	char	*path;
	int		pid;

	pid = fork();
	close(pip_fd[1]);
	if (pid == 0)
	{
		outfile_fd = open(argv[i + 1], O_TRUNC | O_CREAT | O_RDWR, 00644);
		if (outfile_fd < 0)
			error_handle(argv[i + 1], 2);
		dup2(pip_fd[0], 0);
		dup2(outfile_fd, 1);
		cmd = ft_split(argv[i], ' ');
		path = get_path(cmd, argv[i], envp);
		if (execve(path, cmd, envp) < 0)
			error_handle(NULL, -1);
		free(path);
		close(outfile_fd);
	}
	close(pip_fd[0]);
	wait(NULL);
}

static void	process_p(int *pip_fd1, int *pip_fd2, char *argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		pid;

	pid = fork();
	close(pip_fd2[0]);
	if (pid == 0)
	{
		dup2(pip_fd1[0], 0);
		dup2(pip_fd2[1], 1);
		cmd = ft_split(argv, ' ');
		path = get_path(cmd, argv, envp);
		if (execve(path, cmd, envp) < 0)
			error_handle(NULL, -1);
		free(path);
	}
	close(pip_fd1[0]);
	close(pip_fd2[1]);
}

static void	pipe_handler(char **argv, char **envp)
{
	int	i;
	int	pid;
	int	pip_fd1[2];
	int	pip_fd2[2];

	i = 3;
	if (pipe(pip_fd1) < 0)
		error_handle(NULL, -1);
	pid = fork();
	if (pid < 0)
		error_handle(NULL, -1);
	if (pid == 0)
		init_p(pip_fd1, argv, envp);
	else if (argv[i + 2])
	{
		if (pipe(pip_fd2) < 0)
			error_handle(NULL, -1);
		pid = fork();
		close(pip_fd1[1]);
		if (pid == 0)
			process_p(pip_fd1, pip_fd2, argv[i], envp);
		i++;
		if (pid != 0)
		{
			close(pip_fd1[0]);
			finish_p(pip_fd2, i, argv, envp);
		}
	}
	else
		finish_p(pip_fd1, i, argv, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;

	i = 0;
	if (argc < 5)
		error_handle(NULL, 0);
	while (i < argc)
	{
		if (*argv[i] == '\0' || argv[i] == NULL)
			error_handle("Invalid arguments\n", 4);
		i++;
	}
	pipe_handler(argv, envp);
	return (0);
}
