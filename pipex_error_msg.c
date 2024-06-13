/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:08:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/13 16:06:18 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
* Shows an error message in the form:
* 	pipex: err_type (: param if needed)
*/
void	pipex_error_msg(char *param, int err)
{
	ft_putstr_fd("pipex: ", 2);
	if (err == CMD_NOT_FOUND)
		ft_putstr_fd("command not found: ", 2);
	if (err == NO_FILE)
		ft_putstr_fd("no such file or directory: ", 2);
	if (err == NO_PERM)
		ft_putstr_fd("permission denied: ", 2);
	if (err == CMD_FAIL)
		ft_putstr_fd("command failed: ", 2);
	if (err == INV_ARGS)
		ft_putstr_fd(ERR_INPUT, 2);
	if (err == NO_MEMORY)
		ft_putstr_fd("no memory left on device", 2);
	if (err == DUP_ERR)
		ft_putstr_fd("could not dup fd", 2);
	if (err == PIPE_ERR)
		ft_putstr_fd("could not create pipe", 2);
	if (err == FORK_ERR)
		ft_putstr_fd("could not fork process", 2);
	if (err == NO_PATH)
		ft_putstr_fd("PATH variable is not set", 2);
	if (param && (err == CMD_NOT_FOUND || err == NO_FILE || err == NO_PERM || \
			err == CMD_FAIL))
		ft_putstr_fd(param, 2);
	ft_putstr_fd("\n", 2);
}

/*
* Shows an error message in the form:
* 	pipex: err_type (: param if needed)
* and frees the child process memory if:
*	~ err = CMD_NOT_FOUND
*	~ err = CMD_FAIL
*/
void	px_error_free(t_pipex *pipex, char *param, int err)
{
	pipex_error_msg(param, err);
	if (err == CMD_NOT_FOUND || err == CMD_FAIL)
		free_child(pipex);
}

/*
* Shows an error message in the form:
* 	pipex: err_type (: param if needed)
* and executes exit(err).
* Useful for finishing all the processes if 
* an error occurs.
*/
void	px_perror_exit(char *param, int err)
{
	pipex_error_msg(param, err);
	exit (err);
}

/*
* Shows an error message when malloc() fails,
* ten exits the program.
*/
void	malloc_error_exit(void)
{
	ft_putstr_fd("pipex: could not allocate memory", 2);
	exit (ERR_MALLOC);
}
