/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:08:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/09 16:57:14 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

int	cmd_error_msg(char *cmd)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("' not  found.\n", 2);
	return (1);
}

void	perror_msg(char	*str)
{
	perror(str);
	exit (1);
}
