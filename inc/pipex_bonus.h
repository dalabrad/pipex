/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:03:24 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/15 11:47:50 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "./pipex.h"
# include <stdbool.h>

typedef struct s_pipex_bonus
{
    int		in_fd;
	int		pid;
	bool	here_doc;
	char	**paths_array;
	char	**cmd_argv;
	char	*cmd_path;

}	t_pipex_bonus;


//  pipex_error_msg_bonus.c

void	prueba(void);

#endif
