/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:48:52 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/18 16:42:32 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	pxb_first_child(t_pipex_bonus *pipex, char **argv, char **envp)
{
	dup2(pipex->pipe[1], STDOUT_FILENO);
	pxb_close_pipes(pipex);
	dup2(pipex->in_fd, STDIN_FILENO);
	pipex->cmd_argv = ft_split(argv[3], ' ');
	pipex->cmd_path = get_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	ft_putstr_fd("First command executing...\n", 2);
	execve(pipex->cmd_path, pipex->cmd_argv, envp);
}

void	pxb_last_child(t_pipex_bonus *pipex, char **argv, char **envp)
{
	if (dup2(pipex->pipe[(pipex->n_cmd - 2) * 2], STDIN_FILENO) == -1)
		px_perror_exit(NULL, DUP_ERR);
	pxb_close_pipes(pipex);
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		px_perror_exit(NULL, DUP_ERR);
	pipex->cmd_argv = ft_split(argv[4], ' ');
	pipex->cmd_path = get_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	ft_putstr_fd("last command executing...\n", 2);
	execve(pipex->cmd_path, pipex->cmd_argv, envp);
}

void	pxb_middle_child(t_pipex_bonus *pipex, char **argv, char **envp, int i)
{
	if (dup2(pipex->pipe[(i - 1) * 2], STDIN_FILENO) == -1)
		px_perror_exit(NULL, DUP_ERR);
	if (dup2(pipex->pipe[(i + 1) * 2 - 1], STDOUT_FILENO) == -1)
		px_perror_exit(NULL, DUP_ERR);
	pxb_close_pipes(pipex);
	pipex->cmd_argv = ft_split(argv[4], ' ');
	pipex->cmd_path = get_cmd_path(pipex->cmd_argv[0], pipex->paths_array);
	ft_putchar_fd('0' + i + 1);
	ft_putstr_fd("º command executing...\n", 2);
	execve(pipex->cmd_path, pipex->cmd_argv, envp);
}

void	pxb_child_selector(t_pipex_bonus *pipex, char **argv,
			char **envp, int i)
{
	if (i == 0)
		pxb_first_child(pipex, argv, envp);
	else if (i + 1 == pipex->n_cmd)
		pxb_last_child(pipex, argv, envp);
	else
		pxb_middle_child(pipex, argv, envp, i);
}
