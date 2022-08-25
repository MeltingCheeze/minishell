#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void runpipe();

int	main(int argc, char **argv)
{
	int	pid;
	int	status;
	int	fd[2];

	pipe(fd);

	switch (pid = fork())
	{
		case 0: /* child */
			runpipe(fd);
			exit(0);

		default: /* parent */
			while ((pid = wait(&status)) != -1)
				fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
			break;

		case -1:
			perror("fork");
			exit(1);
	}
	exit(0);
}

char *cmd1[] = { "/bin/ls", "-al", "/", 0 };
char *cmd2[] = { "/usr/bin/tr", "a-z", "A-Z", 0 };

//         /bin/ls -al / | /usr/bin/tr a-z A-Z
// parent STDOUT(fd[1])     child STDIN(fd[0])
/* fd[1] 파이프의 입력(write) */
/* fd[0] 파이프의 출력(read) */
void	runpipe(int pfd[])
{
	int	pid;

	// 부모 프로세스를 파이프에 대한 표준 출력을 포기하고 자식 프로세스 자체가 exec로 대체
	switch (pid = fork())
	{
		case 0: /* child */
			dup2(pfd[0], STDIN_FILENO);
			// 표준 입력 파일 설명자(0)를 파이프( pfd[0])의 읽기 끝으로 변경
			close(pfd[1]);	/* the child does not need this end of the pipe */
			execvp(cmd2[0], cmd2);
			perror(cmd2[0]);

		default: /* parent */
			dup2(pfd[1], STDOUT_FILENO);
			// 표준 출력 파일 설명자(1)를 파이프( pfd[1])의 쓰기 끝으로 변경
			close(pfd[0]);	/* the parent does not need this end of the pipe */
			execvp(cmd1[0], cmd1);
			perror(cmd1[0]);

		case -1:
			perror("fork");
			exit(1);
	}
}
