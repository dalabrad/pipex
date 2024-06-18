/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:03:24 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/18 11:33:02 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex_bonus.h"

/*
 * Here_doc (reading from stdin) implementation.
*/
static void	pxb_here_doc(t_pipex_bonus *pipex, char **argv)
{
	char	*line;

	pipex->limiter = ft_strjoin(argv[2], "\n");
	if (!pipex->limiter)
		malloc_error_exit();
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			free (pipex->limiter);
			ft_putchar_fd('\n', 2);
			pxb_perror_exit(ERR_HEREDOC_EOF, argv[2]);
		}
		if (!ft_strncmp(line, pipex->limiter, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(pipex->in_fd, line, ft_strlen(line));
		free(line);
	}
	close(pipex->in_fd);
	free (pipex->limiter);
}

/*
 * Function to create the pipes in pipex.pipe.
*/
static void	pxb_create_pipes(t_pipex_bonus *pipex)
{
	int	i;

	pipex->pipe = (int *)malloc((pipex->n_cmd - 1) * 2 * sizeof(int));
	i = 0;
	while (i < (pipex->n_cmd - 1))
	{
		if (pipe(pipex->pipe + 2 * i) == -1)
		{
			free(pipex->pipe);
			px_perror_exit(NULL, PIPE_ERR);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_bonus	pipex;

	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc == 6)
	{
		pipex.here_doc = true;
		pipex.n_cmd = 2;
		pipex.in_fd = open("/tmp/.here_doc", O_CREAT | 01 | O_TRUNC, 0000644);
		if (pipex.in_fd < 0)
			pxb_perror_exit(ERR_HEREDOC, NULL);
		pxb_here_doc(&pipex, argv);
	}
	else if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc >= 5)
	{
		ft_putstr_fd("pipex: multiple pipe implementation coming soon\n", 2);
		exit (0);
/* 		pipex.here_doc = false;
		pipex.n_cmd = argc - 3; */
	}
	else
		pxb_perror_exit(INV_ARGS, NULL);
	pxb_create_pipes(&pipex);
	pipex.in_fd = open("/tmp/.here_doc", O_RDONLY, 0000644);
	if (pipex.in_fd < 0)
		pxb_perror_exit(ERR_RDHEREDOC, NULL);
	pipex.out_fd = open (argv[5], O_APPEND | O_CREAT | O_WRONLY, 0000644);
	if (pipex.out_fd < 0)
		px_perror_exit(argv[5], NO_FILE);
	pipex.paths_array = pipex_path_array(envp);
	pipex.pid = (pid_t *)malloc(sizeof(pid_t) * pipex.n_cmd);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
		pxb_first_child(&pipex, argv, envp);
	waitpid(pipex.pid[0], NULL, 0);
	ft_putstr_fd("First child finished\n", 2);
	pipex.pid[1] = fork();
	if (pipex.pid[1] == 0 && pipex.pid[0] != 0)
		pxb_last_child(&pipex, argv, envp);
	// ERROR DOING EXECVE(wc -l) IN SECOND CHILD, DKH TO SOLVE IT
	waitpid(pipex.pid[1], NULL, 0);
	if (pipex.pid[0] && pipex.pid[1])
		ft_putstr_fd("Second child finished\n", 2);
	pxb_freeparent_closefd(&pipex);
	ft_printf("Parent finished.\n");
	return (0);
}
