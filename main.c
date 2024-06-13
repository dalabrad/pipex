/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:57:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/13 12:48:40 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		px_perror_exit(NULL, INV_ARGS);
	pipex.in_fd = open(argv[1], O_RDONLY);
	pipex.out_fd = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.out_fd < 0)
		pipex_error_msg(argv[4], NO_MEMORY);
	if (pipe(pipex.fd_pipe) < 0)
		px_perror_exit(NULL, PIPE_ERR);
	pipex.paths = get_paths(envp);
	pipex.paths_array = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(&pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0 && pipex.pid1 == 0)
		second_child(&pipex, argv, envp);
	free_parent_closefd(&pipex);
	return (0);
}
