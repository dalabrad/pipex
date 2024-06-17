/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:07:05 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/17 13:53:34 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/*
 * Puts the error message for the error type err.
 *
*/
void	pxb_error_msg(int err)
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
}

void	pxb_perror_exit(int err)
{
	pxb_error_msg(err);
	exit (err);
}
