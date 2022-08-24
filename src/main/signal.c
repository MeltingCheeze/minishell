#include "minishell.h"
# include <readline/readline.h>

void	set_sigaction(struct sigaction *sa_ptr,
						void (*handler)(int, siginfo_t *, void *))
{
	(*sa_ptr).sa_flags = SA_SIGINFO;
	(*sa_ptr).sa_sigaction = handler;
	sigemptyset(&(*sa_ptr).sa_mask);
	if (sigaction(SIGINT, sa_ptr, 0) == -1)
		ft_error("signal(SIGINT) error");
	if (sigaction(SIGQUIT, sa_ptr, 0) == -1)
		ft_error("signal(SIGQUIT) error");
}

void	shell_sigaction(int signo, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signo == SIGINT)
	{
		printf("\n");
		//rl_on_new_line();
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		exit(0); //end_flag = 1;
	}
}
