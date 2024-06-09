/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:57:55 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/09 17:14:05 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*get_cmd_path(char	*cmd, char **paths_array)
{
	char	*tmp;
	char	*cmd_path;

	while (*paths_array)
	{
		tmp = ft_strjoin(*paths_array, "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths_array++;
	}
	return (NULL);
}

void	close_pipe(t_pipex *pipex)
{
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 3)
		return (error_msg(ERR_INPUT));
	if(pipe(pipex.fd_pipe) < 0)
		perror_msg(ERR_PIPE);
	pipex.paths = get_paths(envp);
	pipex.paths_array = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		dup2(pipex.fd_pipe[1], 1);
		close(pipex.fd_pipe[1]);
		pipex.cmd_argv = ft_split(argv[1], ' ');
		pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
		if (!pipex.cmd_path)
		{
			exit(cmd_error_msg(pipex.cmd_argv[0]));
		}
		execve(pipex.cmd_path, pipex.cmd_argv, envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		dup2(pipex.fd_pipe[0], 0);
		close(pipex.fd_pipe[1]);
		pipex.cmd_argv = ft_split(argv[2], ' ');
		pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
		if (!pipex.cmd_path)
		{
			exit(cmd_error_msg(pipex.cmd_argv[0]));
		}
		execve(pipex.cmd_path, pipex.cmd_argv, envp);
	}
	close_pipe(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (free_array(pipex.paths_array), 0);
}
