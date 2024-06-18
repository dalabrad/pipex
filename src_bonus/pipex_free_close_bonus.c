/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_close_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:07:08 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/18 16:04:19 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	pxb_close_pipes(t_pipex_bonus *pipex)
{
	int	i;

	i = 0;
	while (i < ((pipex->n_cmd - 1) * 2))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	pxb_freeparent_closefd(t_pipex_bonus *pipex)
{
	int	i;

	pxb_close_pipes(pipex);
	i = 0;
	while (i < pipex->n_cmd)
	{
		waitpid(pipex->pid[i], NULL, 0);
		ft_printf("Child %d finished.\n", i + 1);
		i++;
	}
	close(pipex->in_fd);
	close(pipex->out_fd);
	free (pipex->pipe);
	free_array(pipex->paths_array);
	free (pipex->pid);
	if (pipex->here_doc)
		unlink ("/tmp/.here_doc");
}
