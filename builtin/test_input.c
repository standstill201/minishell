#include "test_input.h"

t_test_input	*test_lstlast(t_test_input *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_test_input	*test_lstnew(char *env, char *env_name)
{
	t_test_input	*new;

	new = (t_test_input *)malloc(sizeof(t_test_input));
	if (new == NULL)
		exit(1);
	new->key = ft_sturup(env_name);
	new->value = ft_strdup(env);
	new->next = NULL;
	return (new);
}

void	test_lstadd_back(t_test_input **lst, t_test_input *new)
{
	t_test_input	*curr;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = test_lstlast(*lst);
	curr->next = new;
	new->next = NULL;
}

void	get_test_input(t_test_input **arr)
{
	char	env1[] = "/Users/gychoi/Library/Python/3.8/lib/python/site-packages:/Users/gychoi/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/gychoi/Library/Python/3.8/lib/python/site-packages:/Users/gychoi/homebrew/bin\0";
	char	name1[] = "PATH\0"
	char	env2[] = "HOME=/Users/gychoi\0";
	char	name2[] = "HOME\0"
	char	env3[] = "/Users/gychoi/Documents/42curses/minishell/builtin\0";
	char	name3[] = "PWD\0"

	test_lstadd_back(arr, test_lstnew(env1, name1));
	test_lstadd_back(arr, test_lstnew(env2, name2));
	test_lstadd_back(arr, test_lstnew(env3, name3));
}
