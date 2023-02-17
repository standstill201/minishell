/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:25:50 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/14 19:06:41 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_exit(char **argv)
{
	int	status;

	if (argv[1] != NULL)
	{
		ft_putstr_fd("exit\n", 1);
		if (argv[2] != NULL)
		{
			if (!is_numeric(argv[2]))
				exit(255);
			status = ft_atoi(argv[2]);
			exit(status);
		}
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int	ret;

	ft_exit(argv);
	return (0);
}
