/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:03:24 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/19 11:57:44 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/pipex_bonus.h"

/*
 * Function to create the pipes in pipex.pipe.
*/
static void	pxb_create_pipes(t_pipex_bonus *pipex)
{
	int	i;

	pipex->pipe = (int *)malloc((pipex->n_cmd - 1) * 2 * sizeof(int));
	if (!pipex->pipe)
		malloc_error_exit();
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

/*
 * Function to open infile and outfile and store the fd
 * in the pipe struct. Takes into account both situations:
 * 		~ here_doc = true -> infile: here_doc, outfile (append)
 * 		~ here_doc = false -> infile, outfile (truncate)
*/
static void	pxb_open_files(t_pipex_bonus *pipex, int argc, char **argv)
{
	if (pipex->here_doc)
		pipex->in_fd = open("/tmp/.here_doc", O_RDONLY, 0000644);
	else
		pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd < 0)
		pxb_perror_exit(ERR_RDHEREDOC, NULL);
	if (pipex->here_doc)
		pipex->out_fd = open (argv[5], O_APPEND | O_CREAT | O_WRONLY, 0000644);
	else
		pipex->out_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | 01, 0000644);
	if (pipex->out_fd < 0)
		px_perror_exit(argv[5], NO_FILE);
}

static void	pxb_init_pipex(t_pipex_bonus *pipex, int argc, char **argv,
				char **envp)
{
	if (pipex->here_doc)
		pipex->n_cmd = 2;
	else
		pipex->n_cmd = argc - 3;
	pxb_open_files(pipex, argc, argv);
	pipex->paths_array = pipex_path_array(envp);
	pipex->pid = (pid_t *)malloc(sizeof(pid_t) * pipex->n_cmd);
	if (!pipex->pid)
		malloc_error_exit();
	pxb_create_pipes(pipex);
}

static bool	pxb_child_from_parent(t_pipex_bonus pipex, int child_index)
{
	int	i;

	i = 0;
	while (i < child_index)
	{
		if (pipex.pid[i] == 0)
			return (false);
		i++;
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex_bonus	pipex;
	int				i;

	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc == 6)
		pxb_here_doc(&pipex, argv);
	else if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) && argc >= 5)
		pipex.here_doc = false;
	else
		pxb_perror_exit(INV_ARGS, NULL);
	pxb_init_pipex(&pipex, argc, argv, envp);
	i = 0;
	while (i < pipex.n_cmd)
	{
		pipex.pid[i] = fork();
		if (pipex.pid[i] == -1)
		{
			pxb_free_parent(&pipex);
			px_perror_exit(NULL, FORK_ERR);
		}
		else if (pipex.pid[i] == 0 && pxb_child_from_parent(pipex, i))
			pxb_child_selector(&pipex, argv, envp, i);
		i++;
	}
	pxb_freeparent_closefd(&pipex);
	return (0);
}
