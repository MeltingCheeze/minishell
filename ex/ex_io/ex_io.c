#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>

void	unix_error(char *msg)
{
	char	*str_errno;

	printf("%s: %s\n", msg, strerror(errno));
	exit(0);
}

int Open(const char *pathname, int flags, mode_t mode)
{
	int rc;

	if ((rc = open(pathname, flags, mode))  < 0)
	unix_error("Open error");
	return rc;
}

ssize_t Read(int fd, void *buf, size_t count)
{
	ssize_t rc;

	if ((rc = read(fd, buf, count)) < 0)
	unix_error("Read error");
	return rc;
}

ssize_t Write(int fd, const void *buf, size_t count)
{
	ssize_t rc;

	if ((rc = write(fd, buf, count)) < 0)
	unix_error("Write error");
	return rc;
}

void Close(int fd)
{
	int rc;

	if ((rc = close(fd)) < 0)
	unix_error("Close error");
}

void	ex_dup(char *fname)
{
	int	fd1, fd2, fd3;

	fd1 = Open(fname, O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR);
	Write(fd1, "pqrs", 4);

	fd3 = Open(fname, O_APPEND|O_WRONLY, 0);
	Write(fd3, "jklmn", 5);
	fd2 = dup(fd1);  /* Allocates new descriptor */
	Write(fd2, "wxyz", 4);
	Write(fd3, "ef", 2);

	Close(fd1);
	Close(fd2);
	Close(fd3);
}

void	ex_dup2(char *fname)
{
	int		fd1, fd2, fd3;
	char	c1a, c1b, c2a, c2b, c3a, c3b;

	fd1 = open(fname, O_RDONLY, 0);
	fd2 = open(fname, O_RDONLY, 0);
	fd3 = open(fname, O_RDONLY, 0);

	read(fd1, &c1a, 1);
	dup2(fd2, fd1);
	dup2(fd3, fd1);
	read(fd2, &c2a, 1);
	read(fd1, &c1b, 1);
	read(fd2, &c2b, 1);
	read(fd3, &c3a, 1);
	read(fd3, &c3b, 1);
	printf("c1a = %c, c1b = %c\nc2a = %c, c2b = %c\nc3a = %c, c3b = %c\n"
		, c1a, c1b, c2a, c2b, c3a, c3b);

	close(fd1);
	close(fd2);
}

void	ex_read_with_child(char *fname)
{
	int		fd1;
	//int		s;
	char	c1, c2;

	//s = getpid() & 0x1;
	//printf("s : %d\n", s);
	fd1 = Open(fname, O_RDONLY, 0);
	Read(fd1, &c1, 1);
	if (fork() != 0)
	{
		/* Parent */
		usleep(1100);
		Read(fd1, &c2, 1);
		printf("Parent: c1 = %c, c2 = %c\n", c1, c2);
	}
	else
	{
		/* Child */
		Read(fd1, &c2, 1);
		printf("Child: c1 = %c, c2 = %c\n", c1, c2);
		exit(0);
	}
}

int	g_i = 0;

int	main(int argc, char *argv[])
{
	int	*fd;
	int	option;
	int	pid;
	int	status;

	if (argc != 2)
	{
		printf("./ex_io <file_name>");
		exit(0);
	}
	while (1)
	{
		printf("\n=======%d========\n", g_i++);
		printf("1. ex_dup\n2. ex_dup2\n3. ex_read_with_child\n");
		option = atoi(readline("option : "));
		if (option == 1)
			ex_dup(argv[1]);
		else if (option == 2)
			ex_dup2(argv[1]);
		else if (option == 3)
			ex_read_with_child(argv[1]);
		else
			printf("no option\n");
		if (option >= 1 && option <= 3)
		{
			if (!(pid = fork()))
			{
				printf("%s\n", argv[1]);
				char *new_argv[] = {"cat", argv[1], NULL};
				if (execve("/bin/cat", new_argv, NULL) < 0)
				{
					printf("cat: Command not found.\n");
					exit(0);
				}
				printf("\n\n");
			}
			else
			{
				if (waitpid(pid, &status, 0) < 0)
					printf("waitpid error");
			}
		}
	}

}
