/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:33:13 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/14 11:17:26 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <errno.h>
# include <fcntl.h>

# define ERR_INPUT "unvalid argc, use: ./pipex infile cmd1 cmd2 outfile"

enum e_pipex_error
{
	OK_END = 0,
	CMD_NOT_FOUND = -1,
	NO_FILE = -2,
	NO_PERM = -3,
	INV_ARGS = -4,
	NO_MEMORY = -5,
	PIPE_ERR = -6,
	DUP_ERR = -7,
	FORK_ERR = -8,
	NO_PATH = -9,
	CMD_FAIL = -10,
	ERR_MALLOC = -11
};

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd_pipe[2];
	int		in_fd;
	int		out_fd;
	char	**paths_array;
	char	**cmd_argv;
	char	*cmd_path;
}	t_pipex;

//	pipex_error_msg.c

void	pipex_error_msg(char *param, int err);
void	px_error_free(t_pipex *pipex, char *param, int err);
void	px_perror_exit(char *param, int err);
void	malloc_error_exit(void);

//	pipex_free_close.c

void	free_child(t_pipex *pipex);
void	free_parent_closefd(t_pipex *pipex);

//pipex_paths.c

char	**pipex_path_array(char **envp);
char	*get_cmd_path(char	*cmd, char **paths_array);

//	pipex_childs.c

void	first_child(t_pipex *pipex, char **argv, char **envp);
void	second_child(t_pipex *pipex, char **argv, char **envp);

#endif