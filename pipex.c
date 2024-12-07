/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsalah <abdsalah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:53:49 by abdsalah          #+#    #+#             */
/*   Updated: 2024/10/31 10:49:59 by abdsalah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(int *infile, int *outfile, char *infile_name,
		char *outfile_name)
{
	if (access(infile_name, R_OK) < 0)
		error_exit("Permission denied or infile does not exist", NULL, 0);
	*infile = open(infile_name, O_RDONLY);
	if (*infile < 0)
		error_exit("open infile failed", NULL, 0);
	if (access(outfile_name, W_OK) < 0 && access(outfile_name, F_OK) == 0)
		error_exit("Permission denied to write to outfile", (int []){*infile},
			1);
	*outfile = open(outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile < 0)
		error_exit("open outfile failed", (int []){*infile}, 1);
}

void	wait_for_children(int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	files[2];

	files[0] = -1;
	files[1] = -1;
	if (argc < 4)
	{
		write(2, "Usage: ./pipex infile cmd1 ... cmdN outfile\n", 45);
		return (EXIT_FAILURE);
	}
	open_files(&files[0], &files[1], argv[1], argv[argc - 1]);
	execute_pipeline(argc, argv, envp, files);
	close(files[1]);
	wait_for_children(argc - 3);
	return (EXIT_SUCCESS);
}
