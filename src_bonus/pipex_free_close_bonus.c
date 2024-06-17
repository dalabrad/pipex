/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_close_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:07:08 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/17 16:40:30 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	pxb_freeparent_closefd(t_pipex_bonus *pipex)
{
	int	i;

	waitpid(pipex->pid[0], NULL, 0);
	waitpid(pipex->pid[1], NULL, 0);
	close(pipex->in_fd);
	close(pipex->out_fd);
	i = 0;
	while (i < (pipex->n_cmd - 1) * 2)
	{
		close(pipex->pipe[i]);
		i++;
	}
	free (pipex->pipe);
	free_array(pipex->paths_array);
	free (pipex->pid);
	if (pipex->here_doc)
		unlink ("/tmp/.here_doc");
}

void	pxb_close_pipes(t_pipex_bonus *pipex, int no_close)
{
	int	i;

	i = 0;
	while (i < ((pipex->n_cmd - 1) * 2))
	{
		if (i != no_close)
			close(pipex->pipe[i]);
		i++;
	}
}
