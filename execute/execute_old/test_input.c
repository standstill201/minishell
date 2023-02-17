/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:18:50 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/13 19:55:39 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_input.h"

t_test_input	*test_lstlast(t_test_input *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_test_input	*test_lstnew(char **command, int is_meta, int pipe_n)
{
	t_test_input	*new;

	new = (t_test_input *)malloc(sizeof(t_test_input));
	if (new == NULL)
		exit(1);
	new->content = command;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	return (new);
}

void	test_lstadd_back(t_test_input **lst, t_test_input *new)
{
	t_test_input	*curr;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = test_lstlast(*lst);
	curr->next = new;
	new->next = NULL;
}

void	get_test_input(t_test_input **arr)
{
	test_lstadd_back(arr, test_lstnew(, 0, 0));
	test_lstadd_back(arr, test_lstnew("wc -l", 0, 1));
	test_lstadd_back(arr, test_lstnew("cat", 0, 2));
}
