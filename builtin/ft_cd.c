/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:49:01 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/14 15:57:00 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdio.h>

// need to change ft_
int	cd_prev(void)
{
	// chdir(g_vars.prev_path);
	// g_vars.prev_path = getcwd(NULL, 0);
	// if (fail) error;
	// return (ret);
	return (EXIT_SUCCESS);
}

int	exec_cd(char *path)
{
	// g_vars.prev_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	printf("current directory : %s\n", getcwd(NULL, 0));
	return (EXIT_SUCCESS);
}

// prev_path needs to be managed by global variable
// path is changed only in the subshell, so check the path with printf
int	ft_cd(char **command)
{
	char	*cwd;
	int		ret;

	if (command[2] == NULL)
	{
		// g_vars.prev_path = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (EXIT_FAILURE);
		}
		printf("current directory : %s\n", getcwd(NULL, 0));
		return (EXIT_SUCCESS);
	}
	if (ft_strncmp(command[2], "-", 2) == 0)
		ret = cd_prev();
	else
		ret = exec_cd(command[2]);
	return (ret);
}

int	main(int argc, char **argv)
{
	ft_cd(argv);
	return (0);
}
