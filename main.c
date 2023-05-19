/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:24:06 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/19 11:35:37 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"

static size_t	my_strlcat(char *dst, const char *src, size_t dstsize);
static size_t	my_strlcpy(char *dest, const char *src, size_t dstsize)
static char	*my_strjoin(const char *s1, const char *s2);
static void	*my_memcpy(void *dst, const void *src, size_t n);
static size_t	my_strlen(const char *str);
static char	*my_strdup(const char *s1);

int	main(int argc, char *argv[])
{
	char	*line;
	char	*input;
	char	*aux;
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		input = my_strdup("");
		line = get_next_line(fd);
		while (line)
		{
			aux = input;
			input = my_strjoin(input, line);
			free(aux);
				free(line);
			line = get_next_line(fd);
		}
		free(line);
		close(fd);
		printf("%s\n", input);
	}
	return (0);
}

static size_t	my_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = my_strlen((char *)dst);
	if (j <= dstsize)
	{
		while (*(src + i) != '\0' && (j + 1) < dstsize)
		{
			*(dst + j) = *(src + i);
			j++;
			i++;
		}
		*(dst + j) = '\0';
	}
	else
		return (my_strlen((char *)src) + dstsize);
	return (my_strlen(dst) + my_strlen((char *)(src + i)));
}

static size_t	my_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[j])
		j++;
	return (j);
}

static char	*my_strjoin(const char *s1, const char *s2)
{
	size_t	size1;
	size_t	size2;
	char	*str;

	size1 = 0;
	size2 = 0;
	if (s1)
		size1 = my_strlen((char *)s1);
	if (s2)
		size2 = my_strlen((char *)s2);
	str = malloc (sizeof(char) * (size1 + size2 + 1));
	if (!str)
		return (NULL);
	if (s1)
	{
		my_strlcpy(str, s1, size1 + 1);
		my_strlcat((char *)(str + size1), s2, size2 + 1);
	}
	else if (s2)
		my_strlcpy(str, s2, size2 + 1);
	return (str);
}

static void	*my_memcpy(void *dst, const void *src, size_t n)
{
	char		*str1;
	const char	*str2;

	if (!dst && !src)
		return (NULL);
	str1 = (char *)dst;
	str2 = (const char *)src;
	while (n--)
		*str1++ = *str2++;
	return (dst);
}

static size_t	my_strlen(const char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

static char	*my_strdup(const char *s1)
{
	char	*ptr;
	size_t	s1_size;

	s1_size = my_strlen((char *)s1) + 1;
	ptr = malloc (sizeof(char) * s1_size);
	if (!ptr)
		return (NULL);
	my_memcpy(ptr, s1, s1_size);
	return (ptr);
}
