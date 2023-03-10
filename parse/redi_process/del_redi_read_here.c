/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_redi_read_here.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:40:31 by codespace         #+#    #+#             */
/*   Updated: 2023/02/15 21:24:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_list	*redi_append(t_list *temp)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp && temp->is_meta && !ft_iswhite(temp->content[0]))
		unexpected_token_error(temp->content);
	if (!temp)
		unexpected_token_newline();
	temp->fd = open(temp->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	temp->is_fd_add = 1;
	if (temp->fd == -1)
		minishell_error(temp->content);
	return (temp);
}

t_list	*redi_new(t_list *temp)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp && temp->is_meta && !ft_iswhite(temp->content[0]))
		unexpected_token_error(temp->content);
	if (!temp)
		unexpected_token_newline();
	temp->fd = open(temp->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	temp->is_fd_new = 1;
	if (temp->fd == -1)
		minishell_error(temp->content);
	return (temp);
}

t_list	*redi_input(t_list *temp)
{
	temp = temp->next;
	while (temp && temp->is_meta && ft_iswhite(temp->content[0]))
		temp = temp->next;
	if (temp && temp->is_meta && !ft_iswhite(temp->content[0]))
		unexpected_token_error(temp->content);
	if (!temp)
		unexpected_token_newline();
	temp->fd = open(temp->content, O_RDONLY);
	temp->is_fd_input = 1;
	if (temp->fd == -1)
		minishell_error(temp->content);
	return (temp);
}

// int	here_doc_quote(int fd)
// {
// 	char	*line;
// 	char	*tmp;
// 	int		return_fd;

// 	return_fd = create_temp_file();
// 	tmp = get_next_line(fd, 0);
// 	line = ft_strjoin(tmp, "\n");
// 	free(tmp);
// 	while (ft_strlen(line) > 1)
// 	{
		
// 		tmp = get_next_line(fd, 0);
// 		line = ft_strjoin(tmp, "\n");
// 		free(tmp);
// 	}
// }
// << redirect ????????? ?????????. ?????? ??? ???????????? ????????????

t_list	*redi_heredoc(t_list *temp)
{
	while (temp && temp->is_here_word == 0)
		temp = temp->next;
	if (temp)
		temp->fd = read_heredoc_infile(temp->content);
	else
	{
		ft_putstr_fd("I think we've pretty fucked up\n", 2);
		exit(1);
	}
	return (temp);
}

void	del_redi_read_here(t_list **merged_lst)
{
	t_list	*temp;

	temp = *merged_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, "<<", 2) == 0 && temp->is_meta)
			temp = redi_heredoc(temp);
		temp = temp->next;
	}
	temp = *merged_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, ">>", 2) == 0 && temp->is_meta)
			temp = redi_append(temp);
		else if (ft_strncmp(temp->content, ">", 2) == 0 && temp->is_meta)
			temp = redi_new(temp);
		else if (ft_strncmp(temp->content, "<", 2) == 0 && temp->is_meta)
			temp = redi_input(temp);
		temp = temp->next;
	}
	temp = *merged_lst;
}