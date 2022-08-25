#include "minishell.h"
#include <readline/readline.h>

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
	(void)context;
	if (signo == SIGINT)
	{
		if (info->si_pid != 0)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			printf(">>>fork ... si_pid : %d\n", info->si_pid);
		}
	}
	if (signo == SIGQUIT)
	{
		//ft_putstr_fd("", STDERR_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		//ft_putchar_fd('\n', STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		//rl_redisplay();
	}
}
