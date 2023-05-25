/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/25 13:17:56 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	error_usage(void)
{
	ft_putstr_fd("Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n", 2);
	exit(1);
}

void	error_handle(char *filename, int id)
{
	ft_putstr_fd("bash: ", 2);
	if (id == 1 && access(filename, R_OK) < 0)
		perror(filename);
	else if (id == 2 && access(filename, W_OK) < 0)
		perror(filename);
	else if (id == 3)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else if (id == 4)
		ft_putstr_fd(filename, 2);
	else if (id == 5)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(126);
	}
	else if (id < 0)
		perror(NULL);
	exit(1);
}
