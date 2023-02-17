/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:12:44 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/15 21:41:51 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "test_input.h"
#include <stdio.h>

// all meta character follows backslash in export
// 그냥 문자열로 들어왔을 때, 오류메세지 다르게 처리된다. -> 문자열임을 알아야 하나?
// 문자열 안에서 check_validate 다시 한 번 처리.
// 쉼표로 들어온 것에 대해서 파싱 처리 하기.
// 대치 필요

int	is_meta(char c)
{
	// 메타 문자 확인하기
	if (c == '!' || c == '@' || c == '$' || c == '^' || c == '%' || c == ':' \
	|| c == '*' || c == '[' || c == ']' || c == '/' || c == '{' || c == '}' \
	|| c == ',' || c == '.' || c == '?' || c == '+' || c == '~' || c == '-' \
	|| c == '=' || c == '\\' || c == '#' || c == '&' || c == '*' || c == '\'' \
	|| c == '\"' || ft_iswhite(c))
		return (1);
	return (0);
}

int	check_export_type(char *env)
{
	int	i;

	if (env[0] == '\0' || env[0] == '+' || env[0] == '=')
		return (0);
	i = 0;
	while (env[i] != '\0')
	{
		if (is_meta(env[i]))
		{
			if (env[i] == '=')
				return ('=');
			if (env[i] == '+' && env[i + 1] == '=')
				return ('+');
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_key(char *command)
{
	int		i;
	char	*key;

	i = 0;
	while (command[i] != '\0')
	{
		if (is_meta(command[i]))
			break ;
		i++;
	}
	key = (char *)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (command[i] != '\0')
	{
		if (is_meta(command[i]))
			break;
		key[i] = command[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *command)
{
	int		i;
	int		val_count;
	char	*value;

	i = 0;
	val_count = 0;
	while (command[i] != '\0')
	{
		if (val_count)
			val_count++;
		if (is_meta(command[i++]))
			val_count = 1;
	}
	value = (char *)malloc(sizeof(char *) * val_count);
	i = 0;
	val_count = 0;
	while (command[i] != '\0')
	{
		if (val_count)
			value[val_count++ - 1] = command[i];
		if (is_meta(command[i++]))
			val_count = 1;
	}
	value[val_count] = '\0';
	return (value);
}

int	export_replace(t_test_input *arr, char *command)
{
	char	*key;
	char	*value;

	key = get_key(command);
	value = get_value(command);
	while (arr != NULL)
	{
		// safe strncmp needs?
		if (ft_strncmp(arr->key, key, ft_strlen(arr->key) == 0))
			;
	}
}

// arr는 환경 변수를 담은 리스트, argv에는 파싱된 커맨드가 들어온다.
int	ft_export(t_test_input *arr, char **argv)
{
	int	i;
	int	type;
	int	ret;

	if (argv[1] != NULL)
	{
		i = 2;
		while (argv[i] != NULL)
		{
			type = check_export_type(argv[i]);
			if (!type)
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (EXIT_FAILURE);
			}
			else if (type == '=')
				ret = export_replace(arr, argv[i]);
			else if (type == '+')
				ret = export_append(arr, argv[i]);
			else
				ret = export_add(arr, argv[i]);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_test_input	*arr;
	int	i;

	arr = NULL;
	get_test_input(&arr);
	ft_export(arr, argv);
	return (0);
}
