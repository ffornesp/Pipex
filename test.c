/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 10:43:52 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/19 10:58:55 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 2)
	{
		pid = fork();
		if (pid != 0)
			wait(NULL);
		pid = fork();
		if (pid != 0)
			wait(NULL);
		printf("%s from process %d\n", argv[1], pid);
	}
}
