/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 09:31:36 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/25 10:41:00 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	hdoc_to_pipe(int *pip_fd, char *file)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_handle(NULL, -1);
	wait(NULL);
	if (pid == 0)
	{
		close(pip_fd[0]);
		write(pip_fd[1], file, ft_strlen(file));
		close(pip_fd[1]);
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
		outfile_fd = open(file, O_CREAT | O_RDWR, 00644);
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

static void	here_doc_handler(char **argv, char **envp, char *hdoc)
{
	int	i;
	int	pip_fd[2];

	i = 3;
	if (pipe(pip_fd) < 0)
		error_handle(NULL, -1);
	hdoc_to_pipe(pip_fd, hdoc);
	if (argv[i + 2])
		pipe_to_pipe(pip_fd, argv, i, envp);
	else
		pipe_to_file(pip_fd, argv[i], envp, argv[i + 1]);
}

void	here_doc_init(char **argv, char **envp)
{
	char	*input;
	char	*line;
	char	*aux;

	input = ft_strdup("");
	line = get_next_line(0);
	while (line && ft_strncmp(line, argv[2], ft_strlen(argv[2])))
	{
		aux = input;
		input = ft_strjoin(input, line);
		free(aux);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	here_doc_handler(argv, envp, input);
	free(input);
}
