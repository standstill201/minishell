/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:53:17 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/12 22:29:45 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// here are some logic about heredoc
// with pseudo code

char	*get_tmp_filename()
{
	char	buf[100];
	char	*filename;
	int		i;

	i = 0;
	while (1)
	{
		if (access(ft_itoa(i, buf, 10), R_OK) != 0)
			return (buf);
		i++;
	}
	return (NULL);
}

void	write_heredoc(t_list *node, char *filename)
{
	char	*line;
	char	*limiter;

	node->fd_in = open(filename, READ | WRITE | CREAT );
	limiter = node->content[1];
	while (1)
	{
		// need readline?
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			if (ft_strncmp(line + ft_strlen(limiter), "\n", 1) == 0)
			{
				close(node->fd_in);
				break ;
			}
		}
		write(node->fd_in, line, ft_strlen(line));
	}
}

void	heredoc(t_list *node)
{
	int 	fd;
	char	*filename;

	filename = get_tmp_filename();
	write_heredoc(node, filename);
	// if all processes uses heredoc file, then must unlink it
}
