#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char	**environ;

void child(int *pipeline) {
	if (dup2(pipeline[1], STDOUT_FILENO) < 0) {
		exit(1);
	}

	close(pipeline[0]);
	close(pipeline[1]);

	char *argv[] = {
		"/bin/ls",
		"-al",
		NULL
	};

	execve("/bin/ls", argv, environ);
	exit(1);
}

int parent(int *pipeline) {
	const int	outfile = open("hyko", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	char		buf[4096];
	int			status;
	ssize_t		read_size;
	ssize_t		latest_read;

	close(pipeline[1]);

	wait(&status);

	if (WIFEXITED(status)) {
		status = WEXITSTATUS(status);
	} else if (WIFSIGNALED(status)) {
		status = WTERMSIG(status) + 128;
	} else if (WIFSTOPPED(status)) {
		status = SIGSTOP + 128;
	} else {
		status = SIGCONT + 128;
	}

	if (status != EXIT_SUCCESS) {
		return status;
	}

	read(pipeline[0], buf, 4096);
	/*
	dup2(pipeline[0], STDIN_FILENO);
	close(pipeline[0]);
	execve("/bin/cat", ...);
	*/

	close(pipeline[0]);

	write(outfile, buf, read_size);
	close(outfile);

	return status;
}

int main() {
	int		pipeline[2];
	pid_t	pid;

	pipe(pipeline);
	pid = fork();
	if (!pid) {
		child(pipeline);
	} else {
		exit(parent(pipeline));
	}
}
