/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:24:50 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/22 17:59:00 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>

/*static char	*read_file(int fd)
{
	char	*line;
	char	*output;
	char	*aux;

	output = ft_strdup("");
	line = get_next_line(fd);
	while (line)
	{
		aux = output;
		output = ft_strjoin(output, line);
		free(aux);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (output);
}*/

static void	error_handle(char *filename, int id)
{
	if (!filename)
		ft_putstr_fd("Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n", 2);
	else
	{
		ft_putstr_fd("pipex: ", 2);
		if (id == 1 && access(filename, R_OK) < 0)
			perror(filename);
		else if (id == 2 && access(filename, W_OK) < 0)
			perror(filename);
		else if (id < 0)
			perror(NULL);
	}
	exit(0);
}

static void	child_p(int *pip_fd, int infile_fd, char **argv, char **envp)
{
	return ;
}

static void	parent_p(int *pip_fd, int outfile_fd, char **argv, char **envp)
{
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		infile_fd;
	int		outfile_fd;
	int		pip_fd[2];
	int		pid;

	if (argc != 5)
		error_handle(NULL, 0);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		error_handle(argv[1], 1);
	outfile_fd = open(argv[1], O_RDWR);
	if (outfile_fd < 0)
		error_handle(argv[4], 2);
	if (pipe(pip_fd) == -1)
		error_handle(NULL, -1);
	pid = fork();
	if (pid < 0)
		error_handle(NULL, -1);
	if (pid == 0)
		child_p(pip_fd, infile_fd, argv, envp);
	else
		ft_printf("Parent\n");
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
