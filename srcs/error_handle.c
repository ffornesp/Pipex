/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:12:30 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/23 17:58:36 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	error_handle(char *filename, int id)
{
	if (!filename && id == 0)
		ft_putstr_fd("Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n", 2);
	else
	{
		ft_putstr_fd("pipex: ", 2);
		if (id == 1 && access(filename, R_OK) < 0)
			perror(filename);
		else if (id == 2 && access(filename, W_OK) < 0)
			perror(filename);
		else if (id == 3)
		{
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": Command not found\n", 2);
		}
		else if (id < 0)
			perror(NULL);
	}
	exit(0);
}
