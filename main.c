/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:57:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/20 12:45:43 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		px_perror_exit(NULL, INV_ARGS);
	pipex.in_fd = open(argv[1], O_RDONLY);
	pipex.out_fd = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	pipex.paths_array = pipex_path_array(envp);
	if (pipe(pipex.fd_pipe) < 0)
		px_perror_exit(NULL, PIPE_ERR);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		px_perror_exit(NULL, FORK_ERR);
	if (pipex.pid1 == 0)
		first_child(&pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == -1)
		px_perror_exit(NULL, FORK_ERR);
	if (pipex.pid2 == 0 && pipex.pid1 != 0)
		second_child(&pipex, argv, envp);
	free_parent_closefd(&pipex);
	return (0);
}
