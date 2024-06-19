/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:07:05 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/19 11:26:22 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/*
 * Puts the error message for the error type err.
 *
*/
void	pxb_error_msg(int err, char *param)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == INV_ARGS)
	{
		ft_putstr_fd("invalid arguments, use: ", 2);
		ft_putstr_fd("./pipex infile cmd1 cmd2 ... cmdn outfile or ", 2);
		ft_putstr_fd("./pipex here\\_doc LIMITER cmd1 cmd2 outfile\n", 2);
	}
	else if (err == ERR_HEREDOC)
		ft_putstr_fd("error opening here_doc\n", 2);
	else if (err == ERR_RDHEREDOC)
		ft_putstr_fd("error reading from here_doc\n", 2);
	else if (err == ERR_HEREDOC_EOF)
		ft_putstr_fd("here_doc terminated with end-of-file, expected ", 2);
	if (err == ERR_HEREDOC_EOF)
	{
		ft_putstr_fd(param, 2);
		ft_putchar_fd('\n', 2);
	}
}

/*
 * Puts the error message for the error type err.
 * and exits the main with err.
*/
void	pxb_perror_exit(int err, char *param)
{
	pxb_error_msg(err, param);
	exit (err);
}

/*
 * Puts the error message when the cmd id not found in envp.
 * and frees all the memory of the child.
*/
void	pxb_cmd_not_found(t_pipex_bonus *pipex)
{
	pipex_error_msg(pipex->cmd_argv[0], CMD_NOT_FOUND);
	free_array(pipex->cmd_argv);
}

/*
 * Puts the error message when execve() fails and
 * frees all the memory of the child. Then exit(CMD_FAIL).
*/
void	pxb_cmd_fail_exit(t_pipex_bonus *pipex)
{
	pipex_error_msg(pipex->cmd_argv[0], CMD_FAIL);
	free(pipex->cmd_path);
	free_array(pipex->cmd_argv);
	exit (CMD_FAIL);
}
