/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gychoi <gychoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:18:57 by gychoi            #+#    #+#             */
/*   Updated: 2023/02/13 19:54:39 by gychoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_INPUT_H
# define TEST_INPUT_H

# include "executor.h"

typedef struct s_test_input
{
	char			**content;
	int				fd_in;
	int				fd_out;
	struct s_test_input	*next;
}	t_test_input;

void	get_test_input(t_test_input **arr);

#endif
