#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *cmd1[] = { "/bin/ls", "-al", "/", 0 };
char *cmd2[] = { "/usr/bin/tr", "a-z", "A-Z", 0 };

//         /bin/ls -al / | /usr/bin/tr a-z A-Z
// chiled1 STDOUT(fd[1])     child2 STDIN(fd[0])
/* fd[1] 파이프의 입력(write) - src */
/* fd[0] 파이프의 출력(read)  - dest */
void runsource(int pfd[]);
void rundest(int pfd[]);

int	main(int argc, char **argv)
{
	int pid, status;
	int fd[2];

	pipe(fd);

	runsource(fd);
	rundest(fd);
	//close(fd[0]); close(fd[1]); 	/* this is important! close both file descriptors on the pipe */

	while ((pid = wait(&status)) != -1)	/* pick up all the dead children */
		fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
	exit(0);
}

/**
 * 출력을 생성하는 자식(src - read(1)를 닫음)
 * 		표준 출력을 파이프의 쓰기 끝 write(0)으로 설정
 * 해당 데이터를 소비하는 자식 (dest - write(0)를 닫아)
 * 		표준 입력을 동일한 파이프의 읽기 끝 read(1)으로 설정
 * 부모는 더 이상 파이프가 필요하지 않으며 파일 설명자를 닫을 수 있음
 * 		중요! 부모가 파이프(pfd[1])의 쓰기 끝을 닫지 않으면
 * 			파이프 pfd[1]에서 읽고 있는 자식은 절대 종료되지 않음
 * 				              (파일 끝을 읽지 않으므로 )
 * */
void	runsource(int pfd[])	/* run the first part of the pipeline, cmd1 */
{
	int	pid;	/* we don't use the process ID here, but you may wnat to print it for debugging */

	switch (pid = fork())
	{
		case 0: /* child */
			dup2(pfd[1], 1);	/* this end of the pipe becomes the standard output */
			close(pfd[0]); 		/* this process don't need the other end */
			execvp(cmd1[0], cmd1);	/* run the command */
			perror(cmd1[0]);	/* it failed! */

		default: /* parent does nothing */
			break;

		case -1:
			perror("fork");
			exit(1);
	}
}

void rundest(int pfd[])	/* run the second part of the pipeline, cmd2 */
{
	int	pid;

	switch (pid = fork())
	{
		case 0: /* child */
			dup2(pfd[0], 0);	/* this end of the pipe becomes the standard input */
			close(pfd[1]);		/* this process doesn't need the other end */
			execvp(cmd2[0], cmd2);	/* run the command */
			perror(cmd2[0]);	/* it failed! */

		default: /* parent does nothing */
			break;

		case -1:
			perror("fork");
			exit(1);
	}
}
