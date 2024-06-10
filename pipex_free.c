/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:31:56 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 15:56:27 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *
 * This functions frees an array and points it to NULL.
 * 
*/
static void	free_array(char	**array)
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
 * for a child process if the command doesn't exist.
 * 
*/
void	free_child(t_pipex *pipex)
{
	free_array(pipex->cmd_argv);
}

/*
 *
 * This functions frees all the memory allocated
 * for the parent process, and closes the fd of
 * infile and outfile.
 * 
*/
void	free_parent_closefd(t_pipex *pipex)
{
	close(pipex->in_fd);
	close(pipex->out_fd);
	free_array(pipex->paths_array);
}
