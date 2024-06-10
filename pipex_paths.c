/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:01 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/10 14:04:05 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
 *
 * This functions receives the array envp, then scans every
 * string in it until finds the one that starts with: "PATH=".
 * Then returns the pointer to the paths. Returns a string of paths
 * separated with ':'
 * 
*/
char	*get_paths(char **envp)
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

/*
 *
 * This functions test all the paths in the paths_array + "/" + cmd 
 * to test if the command exeutable file is in any of them. Then returns
 * the path of the executable file of the command cmd if exist
 * or a NULL pointer if it doesn't
 * 
*/
char	*get_cmd_path(char	*cmd, char **paths_array)
{
	char	*tmp;
	char	*cmd_path;

	while (*paths_array)
	{
		tmp = ft_strjoin(*paths_array, "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		paths_array++;
	}
	return (NULL);
}
