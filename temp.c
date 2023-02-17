#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "./header/minishell.h"

void	return_char(char **str)
{
	*str = strdup("asdf");
}

// make a test case of execve
int main(int ac, char **av, char **envp)
{
	char *temp;

	return_char(&temp);
	printf("%s\n", temp);
}




// echo				 asdf | >> asdf

// echo

// asdf
 
// |
// >>
// asdf
// ' '
// ehco










// aa'asdf'asdf"asdfzxcv"