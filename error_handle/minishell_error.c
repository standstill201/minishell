/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:53:47 by codespace         #+#    #+#             */
/*   Updated: 2023/02/15 11:17:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	minishell_error(char *error_msg)
{
	write(2, "minishell: ", 11);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, ": ", 2);
	perror("");
	exit(1);
}

void	unexpected_token_error(char *token)
{
	write(2, "minishell: syntax error near unexpected token `", 46);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	exit(1);
}

void	unexpected_token_newline(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	exit(1);
}

void	unexpected_token_end(void)
{
	ft_putstr_fd("minishell: syntax error not ended quote\n", 2);
	exit(1);
}