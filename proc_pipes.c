/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:53:47 by abdsalah          #+#    #+#             */
/*   Updated: 2024/10/31 10:52:05 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int pipefd[2], int i, int argc, int *files)
{
	if (i != argc - 2)
	{
		if (pipe(pipefd) == -1)
			error_exit("pipe failed", files, 2);
	}
	else
		pipefd[1] = files[1];
}

void	process_child(int *nums, int pipefd[2], char *cmd, char **envp)
{
	if (nums[0] != nums[1] - 2)
		close(pipefd[0]);
	handle_command(nums[2], pipefd[1], cmd, envp);
}

void	process_parent(int *prev_pipe_read_end, int pipefd[2], int i, int argc)
{
	close(*prev_pipe_read_end);
	if (i != argc - 2)
	{
		close(pipefd[1]);
		*prev_pipe_read_end = pipefd[0];
	}
}

void	execute_pipeline(int argc, char *argv[], char **envp, int *files)
{
	int		prev_pipe_read_end;
	int		pipefd[2];
	pid_t	pid;
	int		i;

	prev_pipe_read_end = files[0];
	i = 1;
	while (++i < argc - 1)
	{
		create_pipe(pipefd, i, argc, files);
		pid = fork();
		if (pid < 0)
			error_exit("fork failed", (int []){prev_pipe_read_end, pipefd[0],
				pipefd[1]}, 3);
		if (pid == 0)
			process_child((int []){i, argc, prev_pipe_read_end}, pipefd,
				argv[i], envp);
		else
			process_parent(&prev_pipe_read_end, pipefd, i, argc);
	}
}
