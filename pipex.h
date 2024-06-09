/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:33:13 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/09 12:52:17 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_pipe[2];
	int		in_fd;
	int		out_fd;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

//	pipex_error_msg.c

int		error_msg(char *str);
void	perror_msg(char	*str);

#endif