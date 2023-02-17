/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:08:42 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/12 01:49:46 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// write some fuzzy execution logic 
// with pseudo code

void	execute_pipe(t_list *info, char **command)
{
	int		pfd[2];
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[READ_END]);
		dup2(pfd[WRITE_END], info->fd_out);
		close(pfd[WRITED_END]);
		execute_command(command, info->envp);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		close(pfd[WRITE_END]);
		dup2(pfd[READ_END], info->fd_in);
	}
}

void	execute_builtin(t_list *info, char **command)
{
	if (accurate_strncmp(command[0], "cd"))
		ft_echo(command);
	else if
		cd, pwd, export, unset, env, exit;
	// maybe info needs to include envp
}

// make heredoc to file?
void	redirect(t_list *info)
{
	// info needs infile, outfile
	if (redirect '>')
		info->fd_in = open(infile);
	else
		info->fd_in = STDIN_FILENO;
	if (redirect '<')
		info->fd_out = open(outfile);
	else
		info->fd_out = STDOUT_FILENO;
}

void	execution(t_list *head)
{
	t_list	*cur;
	pid_t	pid;
	int		status;
	char	**command;

	pid = fork();
	if (pid == 0)
	{
		// NULL start list head
		cur = head->next;
		while (cur != NULL)
		{
			command = cur->content;
			// need to know redirect file
			if (redirect)
				redirect(cur);
			if (builtin)
				execute_builtin(cur, command);
			else
				execute_pipe(cur, command);
			cur = cur->next;
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}
