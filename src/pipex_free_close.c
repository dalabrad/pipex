/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:31:56 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/20 10:37:52 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
 *
 * This functions frees an array and points it to NULL.
 * 
*/
void	free_array(char	**array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

/*
 *
 * This functions frees all the memory allocated
 * for a child process if the command doesn't exist
 * or execve fails.
 * 
*/
void	free_child(t_pipex *pipex)
{
	free_array(pipex->cmd_argv);
	if (pipex->cmd_path)
		free(pipex->cmd_path);
}

/*
 *
 * This functions frees all the memory allocated
 * for the parent process, and closes the pipe, the fd of
 * infile and outfile and waits for the child processes to finish.
 * 
*/
void	free_parent_closefd(t_pipex *pipex)
{
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
	close(pipex->in_fd);
	close(pipex->out_fd);
	free_array(pipex->paths_array);
}
