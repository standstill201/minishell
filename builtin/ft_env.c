/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:06:28 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/14 17:23:21 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(char **argv, char **envs)
{
	int	i;

	if (argv[1] != NULL)
	{
		i = 0;
		while (envs[i] != NULL)
		{
			ft_putstr_fd(envs[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	**envs;
	char	*env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	envs = (char **)malloc(sizeof(char **) * i + 1);
	i = 0;
	while (envp[i] != NULL)
	{
		env = ft_strdup(envp[i]);
		envs[i] = env;
		i++;
	}
	envs[i] = NULL;
	ft_env(argv, envs);
	return (0);
}
