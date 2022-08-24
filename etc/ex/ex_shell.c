#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <errno.h>
#include "../../lib/libft/libft.h"
# include <termios.h>

#define MAXARGS   128
#define	MAXLINE	 8192  /* Max text line length */

extern char **environ; /* Defined by libc */

/* Function prototypes */
char	*Readline();
void	eval(char *cmdline);
pid_t	Fork(void);
int	parseline(char *buf, char **argv);
int	builtin_command(char **argv);
void	unix_error(char *msg);

/* gcc ex/ex_shell.c ex/libft/libft.a -lreadline -o ex_shell && ./ex_shell */
int	main(void)
{
	char	*cmdline;
	struct termios	save;

	tcgetattr(0, &save);
	cmdline = NULL;
	while (1)
	{
		cmdline = Readline(&save);
		//if (__sfeof(stdin))
		//	exit(0);
		/* Evaluate */
		eval(cmdline);
		free(cmdline);
	}
}

char	*Readline(struct termios *save)
{
	char *line;

	line = readline("Minishell>");
	if (line == NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, save);
		printf("exit\n");
		exit(0);
	}
	add_history(line);
	return (line);
}

void eval(char *cmdline)
{
	char *argv[MAXARGS]; /* Argument list execve() */
	char buf[MAXLINE];   /* Holds modified command line */
	int parse_num;
	pid_t pid;		   /* Process id */
	char	*bin_file;

	ft_strcpy(buf, cmdline);
	parse_num = parseline(buf, argv);
	if (argv[0] == NULL)
		return ;   /* Ignore empty lines */
	if (!builtin_command(argv))
	{
		if ((pid = Fork()) == 0)
		{
			/* Child runs user job */
			bin_file = ft_strjoin("/bin/", argv[0]);
			if (execve(bin_file, argv, environ) < 0)
			{
				printf("%s: Command not found.\n", argv[0]);
				exit(0);
			}
			free(bin_file);
		}
	}
	/* Parent waits for child to terminate */
	if (parse_num)
	{
		int status;
		if (waitpid(pid, &status, 0) < 0)
			unix_error("waitfg: waitpid error");
	}
	return ;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
	if (!ft_strcmp(argv[0], "quit")) /* quit command */
		exit(0);
	return 0;					 /* Not a builtin command */
}

pid_t	Fork(void)
{
	pid_t	pid;

	if ((pid = fork()) < 0)
	unix_error("Fork error");
	return pid;
}

/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
	char	*delim;		/* Points to first space delimiter */
	int		argc;		/* Number of args */

	buf[strlen(buf)] = ' ';
	buf[strlen(buf) + 1] = '\0';
	while (*buf && (*buf == ' ')) /* Ignore leading spaces */
		buf++;

	/* Build the argv list */
	argc = 0;
	while ((delim = ft_strchr(buf, ' ')))
	{
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) /* Ignore spaces */
			buf++;
	}
	argv[argc] = NULL;
	return (argc);
}

void	unix_error(char *msg)
{
	char	*str_errno;

	//str_err = ft_strjoin(msg, ": ");
	//write(2, msg, strlen(msg));
	//free(str_err);
	//str_err = ft_strjoin(strerror(errno), "\n");
	//write(2, str_err, strlen(str_err));
	//free(str_err);
	// exit(1);
	printf("%s: %s\n", msg, strerror(errno));
	exit(0);
}
