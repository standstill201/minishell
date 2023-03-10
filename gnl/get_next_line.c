/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:32:43 by codespace         #+#    #+#             */
/*   Updated: 2023/02/15 20:19:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*re_allocate(char *buffer, char *line)
{
	char	*temp;
	char	*return_val;
	char	*enter_loc;
	char	temp_char;

	enter_loc = ft_strchr(buffer, (int) '\n');
	if (enter_loc)
	{
		temp_char = *(enter_loc + 1);
		*(enter_loc + 1) = 0;
	}
	if (line)
	{
		temp = ft_strdup(line);
		return_val = ft_strjoin(temp, buffer);
		free(line);
		free(temp);
	}
	else
		return_val = ft_strdup(buffer);
	if (enter_loc)
		*(enter_loc + 1) = temp_char;
	return (return_val);
}

void	backup_maker(char *buffer, char **backup)
{
	char	*enter_loc;
	size_t	index;

	index = 0;
	enter_loc = ft_strchr(buffer, (int) '\n') + 1;
	while (*buffer)
		buffer++;
	while (enter_loc < buffer)
	{
		(*backup)[index] = *enter_loc;
		index++;
		enter_loc++;
	}
	(*backup)[index] = 0;
}

char	*backup_enter(char *backup)
{
	char	*return_val;
	char	*enter_loc;
	char	temp_char;
	size_t	index;

	index = 0;
	enter_loc = ft_strchr(backup, (int) '\n');
	temp_char = *(enter_loc + 1);
	*(enter_loc + 1) = 0;
	return_val = ft_strdup(backup);
	*(enter_loc + 1) = temp_char;
	while (index < 7)
	{
		if (!*(enter_loc + index + 1))
			break ;
		backup[index] = *(enter_loc + index + 1);
		index++;
	}
	backup[index] = 0;
	return (return_val);
}

char	*alloc_line(int fd, char *backup, char *line)
{
	char	buffer[7];
	ssize_t	read_size;
	size_t	index;

	index = 0;
	buffer[6] = 0;
	while (index++ < 6)
		buffer[index] = 0;
	read_size = read(fd, buffer, 6);
	while (read_size > 0)
	{
		if (ft_strchr(buffer, (int) '\n'))
		{
			line = re_allocate(buffer, line);
			backup_maker(buffer, &backup);
			return (line);
		}
		else
			line = re_allocate(buffer, line);
		read_size = read(fd, buffer, 6);
		buffer[read_size] = 0;
	}
	if (!read_size)
		backup[0] = 0;
	return (line);
}

char	*get_next_line(int fd, int trg)
{
	char		*line;
	static char	backup[7];

	if (fd < 0)
		return (0);
	line = 0;
	if (trg)
		write(1, "> ", 2);
	if (!backup[0])
	{
		line = alloc_line(fd, backup, line);
		return (line);
	}
	else
	{
		if (ft_strchr(backup, (int) '\n'))
			return (line = backup_enter(backup));
		else
		{
			line = ft_strdup(backup);
			line = alloc_line(fd, backup, line);
			return (line);
		}
	}
	return (line);
}
