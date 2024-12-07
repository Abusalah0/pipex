/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:53:53 by abdsalah          #+#    #+#             */
/*   Updated: 2024/10/31 10:51:35 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *msg, int *fds, int fd_count)
{
	int	i;

	i = -1;
	while (++i < fd_count)
	{
		if (fds[i] != -1)
			close(fds[i]);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}

void	execute_command(char *cmd, char **envp)
{
	char	*args[4];

	args[0] = "/bin/sh";
	args[1] = "-c";
	args[2] = cmd;
	args[3] = NULL;
	execve("/bin/sh", args, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void	handle_command(int input_fd, int output_fd, char *cmd, char **envp)
{
	if (dup2(input_fd, STDIN_FILENO) == -1 || dup2(output_fd, STDOUT_FILENO)
		== -1)
		error_exit("dup2 failed", (int []){input_fd, output_fd}, 2);
	close(input_fd);
	close(output_fd);
	execute_command(cmd, envp);
}
