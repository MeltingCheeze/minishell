#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

int main(void)
{
	int		pipeline[2];
	int		infile = STDIN_FILENO;
	pid_t	pid;

	size_t	cmd_cnt = 2;
	while (cmd_cnt--)
	{
		if (cmd_cnt != 0)
			pipe(pipeline);
		pid = fork();
		if (!pid) //child
		{
			// no use
			if (cmd_cnt != 0)
				close(pipeline[0]);
			// pass output to pipeline/tty
			if (cmd_cnt != 0)
			{
				dup2(pipeline[1], STDOUT_FILENO);
				close(pipeline[1]);
			}
			// recv input from prev pipe/file/tty
			dup2(infile, STDIN_FILENO);
			if (infile != STDIN_FILENO)
				close(infile);

			char *argv[] = {
				"/bin/cat",
				"-e",
				NULL
			};

			execve("/bin/ls", argv, environ); // should pass envp here
			exit(1);
		}
		else //parent
		{
			if (cmd_cnt != 0)
				close(pipeline[1]);
			if (infile != STDIN_FILENO)
				close(infile);
			infile = pipeline[0];
		}
	}

	cmd_cnt++;
	while (cmd_cnt < 2)
	{
		wait(NULL);
		cmd_cnt++;
	}
}
