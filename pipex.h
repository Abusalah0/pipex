/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:43:37 by abdsalah          #+#    #+#             */
/*   Updated: 2024/10/31 08:54:36 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	error_exit(const char *msg, int *fds, int fd_count);
void	handle_command(int input_fd, int output_fd, char *cmd, char **envp);
void	execute_pipeline(int argc, char *argv[], char **envp, int *files);
void	wait_for_children(int cmd_count);

#endif