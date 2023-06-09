/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:24:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/25 15:20:51 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void	child_p(int *pip_fd, char **argv, char **envp)
{
	int		infile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		error_handle(argv[1], 1);
	close(pip_fd[0]);
	dup_and_close(infile_fd, pip_fd[1]);
	exec_cmd(argv[2], envp);
	exit(0);
}

static void	parent_p(int *pip_fd, char **argv, char **envp)
{
	int		outfile_fd;
	int		pid;

	pid = fork();
	close(pip_fd[1]);
	if (pid == 0)
	{
		outfile_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 00644);
		if (outfile_fd < 0)
			error_handle(argv[4], 2);
		if (dup2(pip_fd[0], 0) < 0)
			error_handle(NULL, -1);
		if (dup2(outfile_fd, 1) < 0)
			error_handle(NULL, -1);
		close(outfile_fd);
		exec_cmd(argv[3], envp);
	}
	close(pip_fd[0]);
	wait(NULL);
	wait(NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pip_fd[2];
	int		pid;
	int		i;

	i = 0;
	if (argc != 5)
		error_usage();
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
	if (pid == 0)
		child_p(pip_fd, argv, envp);
	else
		parent_p(pip_fd, argv, envp);
	return (0);
}
