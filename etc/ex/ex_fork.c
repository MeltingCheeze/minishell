#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void	unix_error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}

pid_t Fork(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
	unix_error("Fork error");
	return pid;
}

void Execve(const char *filename, char *const argv[], char *const envp[])
{
	if (execve(filename, argv, envp) < 0)
	unix_error("Execve error");
}

int main(int argc, char *argv[])
{
	pid_t	pid;
	int		x = 1;

	pid = Fork(); //line:ecf:forkreturn
	if (pid == 0)
	{	/* Child */
		printf("child : x=%d\n", ++x); //line:ecf:childprint
		fflush(stdout);
		return 0;
	}
	/* Parent */
	printf("parent: x=%d\n", --x); //line:ecf:parentprint
	fflush(stdout);
	printf("Bye from process %d with x = %d\n", getpid(), x);
	fflush(stdout);
	return 0;
}
