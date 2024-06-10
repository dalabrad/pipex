/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:45:20 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 14:04:45 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * FIRST CHILD PROCESS: 
 * finds the path and the argv of the first command, 
 * then either executes the command if it exist or frees the memory
 * used previously if it dosen't.
*/
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

/*
 * SECOND CHILD PROCESS: 
 * finds the path and the argv of the second command, 
 * then either executes the command if it exist or frees the memory
 * used previously if it dosen't.
*/
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
