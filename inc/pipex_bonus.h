/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:03:24 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/17 17:02:42 by dalabrad         ###   ########.fr       */
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
	ERR_RDHEREDOC = -13
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

void	pxb_error_msg(int err);
void	pxb_perror_exit(int err);

//	pipex_free_close_bonus.c

void	pxb_freeparent_closefd(t_pipex_bonus *pipex);
void	pxb_close_pipes(t_pipex_bonus *pipex, int no_close);

//	pipex_childs_bonus.c

void	pxb_first_child(t_pipex_bonus *pipex, char **argv, char **envp);
void	pxb_last_child(t_pipex_bonus *pipex, char **argv, char **envp);

#endif
