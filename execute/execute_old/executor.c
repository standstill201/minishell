/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:05:04 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/09 21:41:52 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <stdio.h>

char	*find_path(char *command, char **envp)
{
	int		i;
	char	*path;
	char	*find;
	char	**paths;

	if (access(command, F_OK | X_OK) == 0)
		return (command);
	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	find = NULL;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], command);
		if (access(path, F_OK | X_OK) == 0)
			find = ft_strdup(path);
		free(paths[i++]);
		free(path);
	}
	free(paths);
	return (find);
}

int	execute_command(char *content, char **envp)
{
	char	*command;
	char	*path;
	char	**tokens;


	tokens = ft_split(content, ' ');
	command = ft_strjoin("/", tokens[0]);
	path = find_path(command, envp);
	if (tokens == NULL || command == NULL || path == NULL)
		return (-1);
	if (execve(path, tokens, envp) == -1)
		return (-1);
	return (0);
}

void	connect_pipe(t_test_input *arr, char **envp)
{
	int		pfd[2];
	int		status;
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[READ_END]);
		dup2(pfd[WRITE_END], STDOUT_FILENO);
		close(pfd[WRITE_END]);
		status = execute_command(arr->content, envp);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
		close(pfd[WRITE_END]);
		dup2(pfd[READ_END], STDIN_FILENO);
		close(pfd[READ_END]);
	}
}

void	pipeline(t_test_input *arr, char **envp)
{
	while (arr->next != NULL)
	{
		if (ft_strncmp(arr->next->content, "|", 1) == 0)
			connect_pipe(arr, envp);
		arr = arr->next;
	}
	execute_command(arr->content, envp);
}

int main(int argc, char **argv, char **envp)
{
	t_test_input	*arr = NULL;
	int		status;
	pid_t	pid;

	(void)argc;
	(void)argv;

	pid = fork();
	if (pid == 0)
	{
		get_test_input(&arr);
		pipeline(arr, envp);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
