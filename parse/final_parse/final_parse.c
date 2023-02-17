/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:28:00 by codespace         #+#    #+#             */
/*   Updated: 2023/02/16 19:04:31 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	pipe_size_check(t_list *pre_temp, t_list *temp)
{
	int	index;

	index = 0;
	while (pre_temp != temp)
	{
		if (pre_temp && pre_temp->is_meta == 0 && pre_temp->is_here_word == 0
			&& pre_temp->is_fd_input == 0 && pre_temp->is_fd_new == 0
			&& pre_temp->is_fd_add == 0)
			index++;
		pre_temp = pre_temp->next;
		if (pre_temp && pre_temp->is_meta == 0 && pre_temp->is_here_word == 0
			&& pre_temp->is_fd_input == 0 && pre_temp->is_fd_new == 0
			&& pre_temp->is_fd_add == 0 && pre_temp == temp)
			index++;
	}
	return (index);
}

t_list	*cmd_parser(t_list *pre_temp, char **cmd)
{
	int		index;

	index = 0;
	while (pre_temp->is_meta == 1)
		pre_temp = pre_temp->next;
	if (pre_temp)
		*cmd = ft_strdup(pre_temp->content);
	else
		*cmd = NULL;
	return (pre_temp);
}

char	**arg_parser(t_list *pre_temp, char **args, int index)
{
	int		inside_index;

	inside_index = 0;
	while (inside_index < index || index == 0 && inside_index == 0)
	{
		if (pre_temp->is_meta == 0 && pre_temp->is_here_word == 0
			&& pre_temp->is_fd_input == 0 && pre_temp->is_fd_new == 0
			&& pre_temp->is_fd_add == 0)
		{
			args[inside_index] = ft_strdup(pre_temp->content);
			inside_index++;
		}
		pre_temp = pre_temp->next;
	}
	args[inside_index] = NULL;
	return (args);
}

int	*out_in_fd(t_list *pre_temp, t_list *temp)
{
	int	*return_val;

	return_val = (int *)malloc(sizeof(int) * 2);
	return_val[0] = -2;
	return_val[1] = -2;
	while (pre_temp != temp)
	{
		if (pre_temp && pre_temp->is_here_word || pre_temp->is_fd_input)
			return_val[0] = pre_temp->fd;
		else if (pre_temp && pre_temp->is_fd_new || pre_temp->is_fd_add)
			return_val[1] = pre_temp->fd;
		pre_temp = pre_temp->next;
		if (pre_temp && pre_temp->is_here_word || pre_temp->is_fd_input)
			return_val[0] = pre_temp->fd;
		else if (pre_temp && pre_temp->is_fd_new || pre_temp->is_fd_add)
			return_val[1] = pre_temp->fd;
	}
	return (return_val);
}

void	add_t_cmd(t_cmd **return_val, t_list *pre_temp, t_list *temp)
{
	int		index;
	char	**args;
	char	*cmd;
	int		*fds;

	index = pipe_size_check(pre_temp, temp);
	fds = out_in_fd(pre_temp, temp);
	// if (index == 0)
	// 	minishell_error("syntax error near unexpected token `|'");
	pre_temp = cmd_parser(pre_temp, &cmd);
	if (!cmd)
		args = NULL;
	else
	{
		args = (char **)malloc(sizeof(char *) * (index) + 1);
		args = arg_parser(pre_temp, args, index);
	}
	ft_lstadd_back_cmd(return_val, ft_lstnew_cmd(cmd, args));
	ft_lstlast_cmd(*return_val)->pipe_n = temp->pipe_n;
	ft_lstlast_cmd(*return_val)->fd_in = fds[0];
	ft_lstlast_cmd(*return_val)->fd_out = fds[1];
}

t_cmd	*final_parse(t_list **pre_lst)
{
	t_cmd	*return_val;
	t_list	*pre_temp;
	t_list	*temp;

	temp = (*pre_lst)->next;
	pre_temp = temp;
	return_val = NULL;
	while (temp)
	{
		if (temp->next && temp->next->pipe_n != temp->pipe_n)
		{
			add_t_cmd(&return_val, pre_temp, temp);
			pre_temp = temp->next;
		}
		else if (!(temp->next))
			add_t_cmd(&return_val, pre_temp, temp);
		temp = temp->next;
	}
	
	ft_lstclear(pre_lst, free);
	return (return_val);
}
