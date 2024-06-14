/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:22:01 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/14 10:59:25 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

/*
 *
 * This functions receives the array envp, then scans every
 * string in it until finds the one that starts with: "PATH=".
 * Then returns the pointer to the paths. Returns a string of paths
 * separated with ':'
 * 
*/
static char	*get_paths(char **envp)
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
 * Using get_paths and split(paths, ':'), this function
 * returns an array of paths, or finishes the program with:
 *  ~ px_error_exit(NULL, NO_PATH) if no PATH is found in envp.
 * 	~ malloc_error_exit() if memory allocation fails.
 *
*/
char	**pipex_path_array(char **envp)
{
	char	*tmp_paths;
	char	**rtrn;

	tmp_paths = get_paths(envp);
	if (!tmp_paths)
		px_perror_exit(NULL, NO_PATH);
	rtrn = ft_split(tmp_paths, ':');
	if (!rtrn)
		malloc_error_exit();
	return (rtrn);
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
		if (!tmp)
			malloc_error_exit();
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		tmp = NULL;
		if (!cmd_path)
			malloc_error_exit();
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		cmd_path = NULL;
		paths_array++;
	}
	return (NULL);
}
