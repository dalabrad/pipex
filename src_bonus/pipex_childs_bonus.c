/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:48:52 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/17 17:04:07 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	pxb_first_child(t_pipex_bonus *pipex, char **argv, char **envp)
{
	dup2(pipex->pipe[1], STDOUT_FILENO);
	pxb_close_pipes(pipex, 1);
	dup2(pipex->in_fd, STDIN_FILENO);
	pipex->cmd_argv = ft_split(argv[3], ' ');
	pipex->cmd_path = get_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	ft_putstr_fd("First command executing...\n", 2);
	execve(pipex->cmd_path, pipex->cmd_argv, envp);
}

void	pxb_last_child(t_pipex_bonus *pipex, char **argv, char **envp)
{
	if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
		px_perror_exit(NULL, DUP_ERR);
	pxb_close_pipes(pipex, 0);
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		px_perror_exit(NULL, DUP_ERR);
	pipex->cmd_argv = ft_split(argv[4], ' ');
	pipex->cmd_path = get_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	ft_putstr_fd("Second command executing...\n", 2);
	execve(pipex->cmd_path, pipex->cmd_argv, envp);
}
