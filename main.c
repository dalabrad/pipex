/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:57:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/09 13:19:53 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_get_paths(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	size_t	i;

	if (argc != 2)
		return (error_msg("Error\n"));
	ft_printf("Command : '%s'\n\n", argv[1]);
	pipex.paths = ft_get_paths(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	ft_printf("pipex.paths : '%s'\n\n", pipex.paths);
	i = 0;
	while ((pipex.cmd_paths)[i])
	{
		ft_printf("pipex.cmd_paths[%d] : '%s'\n", i, (pipex.cmd_paths)[i]);
		i++;
	}
	return (0);
/* 	int		i, j;
	char	*cmd1_path;
	char	**cmd1_argv;
	char	**paths;

	if (argc != 2)
		ft_error_message("Error\n");
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			paths = ft_split(envp[i] + 5, ':');
			j = 0;
			while (paths[j])
			{
				ft_printf("paths[%d] : '%s'\n", j, paths[j]);
				j++;
			}
			ft_printf("envp[%d] : '%s'", i, envp[i]);
		}
		i++;
	}
	cmd1_argv = ft_split(argv[1], ' ');
	cmd1_path = ft_strjoin("/usr/bin/", cmd1_argv[0]);
	if (execve(cmd1_path, cmd1_argv, NULL) == -1)
		ft_printf("Command '%s' not found.\n", cmd1_argv[0]);
	ft_printf("Oops!! Something went wrong!\n");
	return (0); */
}
