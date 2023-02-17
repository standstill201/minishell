#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main(void)
{
	DIR *dp = NULL;
	struct dirent *entry = NULL;

	if ((dp = opendir("/bin/ls")) == NULL)
	{
		printf("error\n");
		perror("");
		return (-1);
	}
	printf("access: %d\n", access("/bin/ls", F_OK));
	while ((entry = readdir(dp)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}
	
	closedir(dp);
	return (0);
}
