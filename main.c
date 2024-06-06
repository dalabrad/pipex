/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:57:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/06 23:32:59 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int i;

	if (argc != 5)
		ft_error_message("Error\n");
	i = 0;
	while (argv[i])
	{
		ft_printf("arg[%d] : '%s'\n", i, argv[i]);
		i++;
	}
	return (0);
}
