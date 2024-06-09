/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:08:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/09 12:24:13 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

void	perror_msg(char	*str)
{
	perror(str);
	exit (1);
}
