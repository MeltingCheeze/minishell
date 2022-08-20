/* readline rl_on_new_line rl_redisplay add_history */
# include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

char	*ft_readline()
{
	char *line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("Minishell>");
	if (line)
		add_history(line);
	return (line);
}

void	exception(char *msg)
{
	printf("\033[0;31mERROR : %s\n\033[0m", msg);
	exit(1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_sigaction(struct sigaction *sa_ptr,
						void (*handler)(int, siginfo_t *, void *))
{
	(*sa_ptr).sa_flags = SA_SIGINFO;
	(*sa_ptr).sa_sigaction = handler;
	sigemptyset(&(*sa_ptr).sa_mask);
	if (sigaction(SIGINT, sa_ptr, 0) == -1)
		exception("signal(SIGINT) error");
}

void	shell_sigaction(int signo, siginfo_t *info, void *context)
{

	context = (void *)context;
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* gcc -lreadline ex/ex_readline.c -o ex_readline && ./ex_readline */
int	main(void)
{
	char				*line;
	struct sigaction	sa;

	set_sigaction(&sa, shell_sigaction);
	while (42)
	{
		line = ft_readline();
		if (__sfeof(stdin))
			exit(0);
		printf("%s\n", line);
	}
}
