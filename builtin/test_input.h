#ifndef TEST_INPUT_H
# define TEST_INPUT_H

# include "builtin.h"

typedef struct s_test_input
{
	char				*key;
	char				*value;
	struct s_test_input	*next;
}	t_test_input;

void	get_test_input(t_test_input **arr);

#endif
