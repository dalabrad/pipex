/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:03:24 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/15 12:08:16 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			*limiter;
	t_pipex_bonus	pipex;
	
	if (argc != 4)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		return (2);
	pipex.in_fd = open("/tmp/.here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (pipex.in_fd  < 0)
		return (3);
	limiter = ft_strjoin(argv[2], "\n"); 
	while (1)
	{
		write (1, ">", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, limiter, ft_strlen(line)) || !line)
		{
			free(line);
			line = NULL;
			break ;
		}
		write(pipex.in_fd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	close(pipex.in_fd);
	free (limiter);
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		 pipex.in_fd = open("/tmp/.here_doc", O_RDONLY);
        if (pipex.in_fd < 0)
            return (5);
        dup2(pipex.in_fd, STDIN_FILENO);
        close(pipex.in_fd);
		pipex.paths_array = pipex_path_array(envp);
		pipex.cmd_argv = ft_split(argv[3], ' ');
		pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
		execve(pipex.cmd_path, pipex.cmd_argv, envp);
	}
	close(pipex.in_fd);
	waitpid(pipex.pid, NULL, 0);
	unlink("/tmp/.here_doc");
	return (0);
}
