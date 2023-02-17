/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:03:19 by seokjyoo          #+#    #+#             */
/*   Updated: 2023/02/16 20:50:50 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	main(void)
{
	char	*line;
	t_cmd	*line_root;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (line[0] != '\0')
			add_history(line);
		line_root = parse_data(line);
		execute(line_root);
		t_cmd	*temp = line_root;
		while (temp)
		{
			printf("--------------------------\n");
			printf("cmd: %s\n", temp->cmd);
			for (int i = 0; temp->args[i]; i++)
				printf("args %d: %s\n", i, temp->args[i]);
			printf("fd_in: %d\n", temp->fd_in);
			// read fd_in
//				char buf[100];
//				int ret = read(temp->fd_in, buf, 100);	
//				buf[ret] = '\0';
//				printf("buf: %s\n", buf);
			printf("fd_out: %d\n", temp->fd_out);
			printf("pipe_n: %d\n", temp->pipe_n);
			printf("--------------------------\n");
			temp = temp->next;
		}
		free(line);
//		while(1)
//			continue ;
	}
}

// int main(int ac, char *av[])
// {
// 	t_list	*return_val;
// 	char	**return_val_char;
// 	int		index;

// 	index = 0;
// 	return_val = seperate_string("< infile cat");
// 	set_pipe_n(&return_val);
// 	set_env(&return_val);
// 	t_list	*temp = merge_string(&return_val);
// 	while (temp)
// 	{
// 		printf("--------------------------\n");
// 		printf("is_meta: %d\n", temp->is_meta);
// 		printf("pipe_n: %d\n", temp->pipe_n);
// 		printf("content: $%s$\n", temp->content);
// 		printf("--------------------------\n");
// 		temp = temp->next;
// 	}
// 	// ft_lstclear(&(temp->next), free);
// 	// free(temp->content);
// 	// free(temp);
// 	return (0);
// }
