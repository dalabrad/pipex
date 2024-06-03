/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:57:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/03 16:19:34 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"

int	main(int argc, char **argv)
{
	int i;

	if (argc != 5)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	i = 0;
	while (argv[i])
	{
		ft_printf("arg[%d] : '%s'\n", i, argv[i]);
		i++;
	}
	return (0);
}
