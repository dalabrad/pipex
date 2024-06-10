/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:45:20 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 17:06:13 by dalabrad         ###   ########.fr       */
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
	dup2(pipex.fd_pipe[1], STDIN_FILENO);
	close(pipex.fd_pipe[1]);
	dup2(pipex.in_fd, STDOUT_FILENO);
	pipex.cmd_argv = ft_split(argv[2], ' ');
	pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
	if (!pipex.cmd_path)
	{
		cmd_not_found(pipex.cmd_argv[0]);
		free_child(&pipex);
		exit (EXIT_FAILURE);
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
	dup2(pipex.fd_pipe[0], STDIN_FILENO);
	close(pipex.fd_pipe[1]);
	dup2(pipex.out_fd, STDOUT_FILENO);
	pipex.cmd_argv = ft_split(argv[3], ' ');
	pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
	if (!pipex.cmd_path)
	{
		cmd_not_found(pipex.cmd_argv[0]);
		free_child(&pipex);
		exit (EXIT_FAILURE);
	}
	execve(pipex.cmd_path, pipex.cmd_argv, envp);
}
