/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:38:41 by ffornes-          #+#    #+#             */
/*   Updated: 2023/05/25 09:38:02 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	error_usage(void);
void	error_handle(char *filename, int id);

void	exec_cmd(char *argv, char **envp);
void	dup_and_close(int fd_1, int fd_2);

char	*get_path(char **cmd, char *line_cmd, char **envp);

void	here_doc_init(char **argv, char **envp);

#endif
