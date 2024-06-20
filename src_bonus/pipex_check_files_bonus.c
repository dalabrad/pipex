/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check_files_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:48:38 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/20 13:17:08 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	pxb_check_infile(t_pipex_bonus *pipex, char **argv)
{
	if (pipex->here_doc)
		pxb_error_msg(ERR_RDHEREDOC, NULL);
	else
	{
		if (access(argv[1], R_OK) == -1 && !access(argv[1], F_OK))
			pipex_error_msg(argv[1], NO_PERM);
		else
			pipex_error_msg(argv[1], NO_FILE);
	}
}

void	pxb_check_outfile(t_pipex_bonus *pipex, char **argv)
{
	if (pipex->here_doc)
	{
		if (access(argv[5], W_OK) == -1 && !access(argv[5], F_OK))
			pipex_error_msg(argv[5], NO_PERM);
		else
			pipex_error_msg(argv[5], NO_MEMORY);
		return ;
	}
	else
	{
		if (access(argv[pipex->n_cmd + 2], W_OK) == -1
			&& !access(argv[pipex->n_cmd + 2], F_OK))
			pipex_error_msg(argv[pipex->n_cmd + 2], NO_PERM);
		else
			pipex_error_msg(argv[pipex->n_cmd + 2], NO_MEMORY);
		return ;
	}
}
