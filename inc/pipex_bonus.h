/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:03:24 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/18 17:51:45 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "./pipex.h"
# include <stdbool.h>

enum e_pxb_error
{
	ERR_HEREDOC = -12,
	ERR_RDHEREDOC = -13,
	ERR_HEREDOC_EOF = -14
};

typedef struct s_pipex_bonus
{
	int		in_fd;
	int		out_fd;
	int		*pipe;
	int		n_cmd;
	pid_t	*pid;
	bool	here_doc;
	char	**paths_array;
	char	**cmd_argv;
	char	*cmd_path;

}	t_pipex_bonus;

//  pipex_error_msg_bonus.c

void	pxb_error_msg(int err, char *param);
void	pxb_perror_exit(int err, char *param);

//	pipex_free_close_bonus.c

void	pxb_close_pipes(t_pipex_bonus *pipex);
void	pxb_freeparent_closefd(t_pipex_bonus *pipex);

//	pipex_childs_bonus.c

void	pxb_first_child(t_pipex_bonus *pipex, char **argv, char **envp);
void	pxb_last_child(t_pipex_bonus *pipex, char **argv, char **envp);
void	pxb_child_selector(t_pipex_bonus *pipex, char **argv, char **envp,
			int i);

//	pipex_here_doc_bonus.c

void	pxb_here_doc(t_pipex_bonus *pipex, char **argv);

#endif
