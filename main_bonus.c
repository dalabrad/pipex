/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:03:24 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/17 13:23:41 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	char			*limiter;
	int				i;
	t_pipex_bonus	pipex;
	
	if (argc < 5)
		pxb_perror_exit(INV_ARGS);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc == 6)
	{
		pipex.here_doc = true;
		pipex.n_cmd = 2;
	}
	else if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		pipex.here_doc = false;
		pipex.n_cmd = argc - 3;
	}
	// The rest is for pipex.here_doc == true.
	pipex.in_fd = open("/tmp/.here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (pipex.in_fd  < 0)
		pxb_perror_exit(ERR_HEREDOC);
	limiter = ft_strjoin(argv[2], "\n");
	if (!limiter)
		malloc_error_exit();
	while (1) //here_doc reading implementation.
	{
		write (1, "> ", 2);
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
	limiter = NULL;
	pipex.pipe = (int *)malloc((pipex.n_cmd - 1) * 2 * sizeof(int)); //preparing the pipes
	i = 0;
	while (i < (pipex.n_cmd - 1)) //piping
	{
		if (pipe(pipex.pipe + 2 * i) == -1)
		{
			free(pipex.pipe);
			px_perror_exit(NULL, PIPE_ERR);
		}
		i++;
	}
	ft_printf("Pipes created succesfully\n");
	pipex.in_fd = open("/tmp/.here_doc", O_RDONLY); //opening the here_doc for reading
	if (pipex.in_fd < 0)
		pxb_perror_exit(ERR_RDHEREDOC);
	ft_printf("Here_doc opened succesfully\n");
	pipex.out_fd = open (argv[5], O_APPEND | O_CREAT | O_WRONLY, 0000644); //opening the outfile in append mode
	if (pipex.out_fd < 0)
		px_perror_exit(argv[5], NO_FILE);
	ft_printf("outfile opened succesfully\n");
	pipex.paths_array = pipex_path_array(envp);
	pipex.pid = fork(); //first child
	if (pipex.pid == 0)
	{
 		dup2(pipex.pipe[1], STDOUT_FILENO);
		pxb_close_pipes(&pipex, 1);
		dup2(pipex.in_fd, STDIN_FILENO);
		pipex.cmd_argv = ft_split(argv[3], ' ');
		pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
		ft_putstr_fd(pipex.cmd_path, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("First command executing...\n", 2);
		execve(pipex.cmd_path, pipex.cmd_argv, envp);
	}
	waitpid(pipex.pid, NULL, 0);
	ft_putstr_fd("First child finished\n", 2);
	pipex.pid = fork(); //second child
	if (pipex.pid == 0)
	{
		dup2(pipex.pipe[0], STDIN_FILENO);
		pxb_close_pipes(&pipex, 0);
		dup2(pipex.out_fd, STDOUT_FILENO);
		pipex.cmd_argv = ft_split(argv[4], ' ');
		pipex.cmd_path = get_cmd_path(pipex.cmd_argv[0], pipex.paths_array);
		ft_putstr_fd(pipex.cmd_path, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("Second command executing...\n", 2);
		execve(pipex.cmd_path, pipex.cmd_argv, envp);
	}
	pxb_freeparent_closefd(&pipex);
	ft_printf("Parent finished.\n");
	return (0);
}
