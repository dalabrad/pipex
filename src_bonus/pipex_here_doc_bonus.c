/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:29:29 by dalabrad          #+#    #+#             */
/*   Updated: 2024/06/18 18:01:55 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

/*
 * Function:
    1) Shows '> ' in stdout.
    2) tries to read a line from stdin.
    3) Either:
		~ Writes line in here_doc. 
		~ Breaks if end-of-file or LIMITER is found in line.
          (end-of-file will exit() main with a perror).
*/
static void	pxb_here_doc_read(t_pipex_bonus *pipex, char *limiter)
{
	char	*line;

	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			ft_putchar_fd('\n', 2);
			pxb_perror_exit(ERR_HEREDOC_EOF, limiter);
		}
		if (!ft_strncmp(line, limiter, ft_strlen(line) - 1))
		{
			free(line);
			return ;
		}
		write(pipex->in_fd, line, ft_strlen(line));
		free(line);
	}
}

/*
 * Here_doc (reading from stdin) implementation:
        1) Opens here_doc.
        2) sets pipex.here_doc to true.
        3) reads from stdin to here_doc
        4) closes here_doc.
*/
void	pxb_here_doc(t_pipex_bonus *pipex, char **argv)
{
	char	*limiter;

	pipex->in_fd = open("/tmp/.here_doc", O_CREAT | 01 | O_TRUNC, 0000644);
	if (pipex->in_fd < 0)
		pxb_perror_exit(ERR_HEREDOC, NULL);
	pipex->here_doc = true;
	limiter = argv[2];
	pxb_here_doc_read(pipex, limiter);
	close(pipex->in_fd);
}
