/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:45:20 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/13 12:27:11 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 * FIRST CHILD PROCESS: 
 * finds the path and the argv of the first command, 
 * then either executes the command if it exist or frees the memory
 * used previously if it dosen't.
*/
void	first_child(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->in_fd < 0)
	{
		if (access(argv[1], R_OK) == -1 && !access(argv[1], F_OK))
			pipex_error_msg(argv[1], NO_PERM);
		else
			pipex_error_msg(argv[1], NO_FILE);
		return ;
	}
	dup2(pipex->fd_pipe[1], STDIN_FILENO);
	close(pipex->fd_pipe[1]);
	dup2(pipex->in_fd, STDOUT_FILENO);
	pipex->cmd_argv = ft_split(argv[2], ' ');
	pipex->cmd_path = get_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	if (!pipex->cmd_path)
	{
		px_error_free(pipex, pipex->cmd_argv[0], CMD_NOT_FOUND);
		return ;
	}
	if (execve(pipex->cmd_path, pipex->cmd_argv, envp) == -1)
		px_error_free(pipex, pipex->cmd_argv[0], CMD_FAIL);
}

/*
 * SECOND CHILD PROCESS: 
 * finds the path and the argv of the second command, 
 * then either executes the command if it exist or frees the memory
 * used previously if it dosen't.
*/
void	second_child(t_pipex *pipex, char **argv, char **envp)
{
	dup2(pipex->fd_pipe[0], STDIN_FILENO);
	close(pipex->fd_pipe[1]);
	dup2(pipex->out_fd, STDOUT_FILENO);
	pipex->cmd_argv = ft_split(argv[3], ' ');
	pipex->cmd_path = get_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	if (!pipex->cmd_path)
	{
		px_error_free(pipex, pipex->cmd_argv[0], CMD_NOT_FOUND);
		return ;
	}
	if (execve(pipex->cmd_path, pipex->cmd_argv, envp) == -1)
		px_error_free(pipex, pipex->cmd_argv[0], CMD_FAIL);
}
