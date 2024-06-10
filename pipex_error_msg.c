/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:08:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 15:52:03 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *
 * This functions prints str in stderr and returns 1
 * 
*/
int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

/*
 *
 * This functions prints "zsh: command not found: cmd\n" in 
 * stderr and returns 1.
 * 
*/
int	cmd_not_found(char *cmd)
{
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

/*
 *
 * This functions prints "zsh: no such file or directory: filename\n" in 
 * stderr and calls exit (1).
 * 
*/
void	file_error(char *file_name)
{
	ft_putstr_fd("zsh: no such file or directory: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

/*
 *
 * This functions prints a perror(str) and
 * uses exit (1). Is used for an error opening a file.
 * 
*/
void	perror_msg(char	*str)
{
	perror(str);
	exit (1);
}
