/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:33:13 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 16:42:38 by dalabrad         ###   ########.fr       */
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

# define ERR_INPUT "Error, use: ./pipex infile cmd1 cmd2 outfile\n"
# define ERR_PIPE "Pipe"
# define ERR_FORK "Fork"

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_pipe[2];
	int		in_fd;
	int		out_fd;
	char	*paths;
	char	**paths_array;
	char	**cmd_argv;
	char	*cmd_path;
}	t_pipex;

//	pipex_error_msg.c

int		error_msg(char *str);
int		cmd_not_found(char *cmd);
void	perror_msg(char	*str);
void	file_error(char *file_name);

//	pipex_free.c

void	free_child(t_pipex *pipex);
void	free_parent_closefd(t_pipex *pipex);

//pipex_paths.c

char	*get_paths(char **envp);
char	*get_cmd_path(char	*cmd, char **paths_array);

//	pipex_childs.c

void	first_child(t_pipex pipex, char **argv, char **envp);
void	second_child(t_pipex pipex, char **argv, char **envp);

#endif