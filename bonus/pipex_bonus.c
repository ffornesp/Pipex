/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:24:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/25 15:20:02 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include "pipex_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static void	file_to_pipe(int *pip_fd, char *argv, char **envp, char *file)
{
	int	infile_fd;
	int	pid;

	pid = fork();
	if (pid < 0)
		error_handle(NULL, -1);
	wait(NULL);
	if (pid == 0)
	{
		close(pip_fd[0]);
		infile_fd = open(file, O_RDONLY);
		if (infile_fd < 0)
			error_handle(file, 1);
		dup_and_close(infile_fd, pip_fd[1]);
		exec_cmd(argv, envp);
		exit(0);
	}
}

static void	pipe_to_file(int *pip_fd, char *argv, char **envp, char *file)
{
	int	outfile_fd;
	int	pid;

	close(pip_fd[1]);
	pid = fork();
	if (pid < 0)
		error_handle(NULL, -1);
	wait(NULL);
	if (pid == 0)
	{
		outfile_fd = open(file, O_TRUNC | O_CREAT | O_RDWR, 00644);
		if (outfile_fd < 0)
			error_handle(file, 2);
		dup_and_close(pip_fd[0], outfile_fd);
		exec_cmd(argv, envp);
		exit(0);
	}
	close(pip_fd[0]);
}

static void	pipe_to_pipe(int *pip_fd1, char **argv, int i, char **envp)
{
	int	pip_fd2[2];
	int	pid;

	if (pipe(pip_fd2) < 0)
		error_handle(NULL, -1);
	close(pip_fd1[1]);
	pid = fork();
	if (pid < 0)
		error_handle(NULL, -1);
	if (pid == 0)
	{
		close(pip_fd2[0]);
		dup_and_close(pip_fd1[0], pip_fd2[1]);
		exec_cmd(argv[i], envp);
		exit(0);
	}
	if (wait(NULL) != 0)
		i++;
	close(pip_fd1[0]);
	if (argv[i + 2])
		pipe_to_pipe(pip_fd2, argv, i, envp);
	else
		pipe_to_file(pip_fd2, argv[i], envp, argv[i + 1]);
}

static void	pipe_handler(char **argv, char **envp)
{
	int	i;
	int	pip_fd[2];

	i = 3;
	if (pipe(pip_fd) < 0)
		error_handle(NULL, -1);
	file_to_pipe(pip_fd, argv[2], envp, argv[1]);
	if (argv[i + 2])
		pipe_to_pipe(pip_fd, argv, i, envp);
	else
		pipe_to_file(pip_fd, argv[i], envp, argv[i + 1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;

	i = 0;
	if (argc < 5)
		error_usage();
	while (i < argc)
	{
		if (*argv[i] == '\0' || argv[i] == NULL)
			error_handle("Invalid arguments\n", 4);
		i++;
	}
	if (!ft_strncmp(argv[1], "here_doc", 8))
		here_doc_init(argv, envp);
	else
		pipe_handler(argv, envp);
	return (0);
}
