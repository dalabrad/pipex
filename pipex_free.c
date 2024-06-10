/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:31:56 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 13:01:20 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_child(t_pipex *pipex)
{
	free(pipex->cmd_path);
	pipex->cmd_path = NULL;
	free_array(pipex->cmd_argv);
}

void	free_parent(t_pipex *pipex)
{
	free_array(pipex->paths_array);
}
