/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:55:27 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/14 16:02:36 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_option(char *option)
{
	int	i;

	// need to convert ft_
	if (ft_strncmp(option, "-n", 2) == 0)
	{
		i = 2;
		while (option[i] != '\0')
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

// echo returns only EXIT_SUCCESS
int	ft_echo(char **command)
{
	int	i;
	int	option;

	i = 2;
	option = 0;
	if (command[i] && check_option(command[i]))
	{
		option = 1;
		i++;
	}
	while (command[i])
	{
		// need to convert ft_
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	ft_echo(argv);
	return (0);
}
