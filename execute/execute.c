/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 01:08:42 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/16 22:01:35 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/execute.h"
#include <stdio.h> // must delete!

extern char	**environ;	// 임시 env

char	*find_path(char *command)
{
	int		i;
	char	*path;
	char	*find;
	char	**paths;

	if (access(command, F_OK | X_OK) == 0)
		return (command);
	i = 0;
	while (ft_strncmp(environ[i], "PATH=", 5))
		i++;
	if (environ[i] == NULL)
		return (NULL);
	paths = ft_split(environ[i] + 5, ':');
	i = 0;
	find = NULL;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], command);
		if (access(path, F_OK | X_OK) == 0)
			find = ft_strdup(path);
		free(path);
		free(paths[i++]);
	}
	free(paths);
	return (find);
}

int	execute_command(t_cmd *node)
{
	char	*command;
	char	*path;

	command = ft_strjoin("/", node->cmd);
	path = find_path(command);
	if (command == NULL || path == NULL)
		return (0);
	if (execve(path, node->args, environ) == -1)
	{
		free(command);
		free(path);
		printf("EXECVE FAILED\n");
		// free(args);
	}
	return (0);
}

// env에 대한 정보가 필요하다.
// return value에 대한 고민
int	execute_builtin(t_cmd *node)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
	{
		ft_putstr_fd("PROD: ECHO EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "cd", 3) == 0)
	{
		ft_putstr_fd("PROD: CD EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "pwd", 4) == 0)
	{
		ft_putstr_fd("PROD: PWD EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "export", 7) == 0)
	{
		ft_putstr_fd("PROD: EXPORT EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "unset", 6) == 0)
	{
		ft_putstr_fd("PROD: UNSET EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "env", 4) == 0)
	{
		ft_putstr_fd("PROD: ENV EXECUTED\n", 1);
		exit(1);
	}
	else if (ft_strncmp(node->cmd, "exit", 5) == 0)
	{
		ft_putstr_fd("PROD: EXIT EXECUTED\n", 1);
		exit(1);
	}
	return (ret);
}

// need to add FUNCTION_GUARD
static int	pipeline(t_cmd *node)
{
	int		pfd[2];
	int		status;
	pid_t	pid;

	pipe(pfd);
	pid = fork();
	if (pid == -1)
		minishell_error("fork error");
	else if (pid == 0)
	{
		close(pfd[READ_END]);
		dup2(pfd[WRITE_END], STDOUT_FILENO);
		close(pfd[WRITE_END]);
		// need to check error message
		if (!execute_builtin(node))
			if (!execute_command(node))
				minishell_error("command not found\n");
	}
	else
	{
		waitpid(pid, &status, WNOHANG);
		close(pfd[WRITE_END]);
		dup2(pfd[READ_END], STDIN_FILENO);
		close(pfd[READ_END]);
	}
	return (status);
}

// fd_in, fd_out에 대해서도 다뤄야 한다.
int	execute(t_cmd *root)
{
	t_cmd	*node;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		minishell_error("fork error");
	else if (pid == 0)
	{
		node = root;
		while (node->next != NULL)
		{
			// should get return value
			pipeline(node);
			node = node->next;
		}
		// need to check error message
		if (!execute_builtin(node))
			if (!execute_command(node))
				minishell_error("command not found\n");
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
