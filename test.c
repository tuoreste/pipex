#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
    char *command = "/bin/ls";
    char *args[3] = { "ls", "-l", NULL };
	int fd[2];

	pid_t id = fork();
	if (id == 0)
	{
		execve(NULL, args, NULL);
		perror("command not found");
		exit(1);
	}
	pipe(fd);
	
	wait(NULL);
	printf("This won't be printed\n");
	return (0);
}
