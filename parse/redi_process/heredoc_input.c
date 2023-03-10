/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:07:03 by codespace         #+#    #+#             */
/*   Updated: 2023/02/15 22:21:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	up_digit(char *str, int index)
{
	str[index] = '!';
	if (index > 0)
	{
		if (str[index - 1] == '~')
			up_digit(str, index - 1);
		else
			str[index - 1]++;
	}
}

char	*name_creator(void)
{
	char	*str;
	int		index;
	char	*return_val;

	str = ft_strdup("!!!!!");
	return_val = ft_strjoin("/tmp/", str);
	index = ft_strlen(return_val) - 1;
	free(str);
	while (access(return_val, F_OK) == 0)
	{
		if (return_val[index] == '~')
			up_digit(return_val, index);
		else
			return_val[index]++;
		if (return_val[index] == '/')
			return_val[index] = 'f';
	}
	return (return_val);
}

// int	create_temp_file(void)
// {
// 	char	*str;
// 	int		fd;

// 	str = name_creator();
// 	fd = open(str, O_CREAT | O_RDWR, 0644);
// 	unlink(str);
// 	free(str);
// 	return (fd);
// }

// int	read_heredoc_infile(char *limiter)
// {
// 	int		fd;
// 	char	*line;
// 	char	*lim;
// 	int		temp_fd;

// 	fd = create_temp_file();
// 	lim = (char *)ft_calloc(ft_strlen(limiter) + 2, 1);
// 	ft_memcpy(lim, limiter, ft_strlen(limiter));
// 	lim[ft_strlen(limiter)] = '\n';
// 	line = get_next_line(STDIN_FILENO, 1);
// 	while (line && ft_strncmp(line, lim, ft_strlen(lim)))
// 	{
// 		write(fd, line, ft_strlen(line));
// 		free(line);
// 		line = get_next_line(STDIN_FILENO, 1);
// 	}
// 	free(lim);
// 	free(line);
// 	temp_fd = dup(fd);
// 	close(fd);
// 	return (temp_fd);
// }

int	read_heredoc_infile(char *limiter)
{
	int		fd;
	char	*line;
	char	*str;

	str = name_creator();
	fd = open(str, O_CREAT | O_RDWR, 0644);
	line = get_next_line(STDIN_FILENO, 1);
	line[ft_strlen(line) - 1] = '\0';
	while (line && ft_strncmp(line, limiter, ft_strlen(line)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO, 1);
		line[ft_strlen(line) - 1] = '\0';
	}
	close(fd);
	fd = open(str, O_RDONLY);
	unlink(str);
	free(str);
	free(line);
	return (fd);
}



// need to think about ctrl -c and ctrl -d
