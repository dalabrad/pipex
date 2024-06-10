/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:45:20 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 13:03:33 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd_pipe[1], 1);
	close(pipex.fd_pipe[1]);
	pipex.cmd_argv = ft_split(argv[1], ' ');
	pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
	if (!pipex.cmd_path)
	{
		cmd_not_found(pipex.cmd_argv[0]);
		free_child(&pipex);
		exit (1);
	}
	execve(pipex.cmd_path, pipex.cmd_argv, envp);
}

void	second_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.fd_pipe[0], 0);
	close(pipex.fd_pipe[1]);
	pipex.cmd_argv = ft_split(argv[2], ' ');
	pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
	if (!pipex.cmd_path)
	{
		cmd_not_found(pipex.cmd_argv[0]);
		free_child(&pipex);
		exit (1);
	}
	execve(pipex.cmd_path, pipex.cmd_argv, envp);
}
