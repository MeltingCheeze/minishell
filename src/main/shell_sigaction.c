#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

static void	sigint(int si_pid)
{
	if (si_pid != 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		ft_putstr_fd(">>>fork ... si_pid : ", STDOUT_FILENO);
		ft_putnbr_fd(si_pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		// printf(">>>fork ... si_pid : %d\n", si_pid);
		// heexit 
	}
}

static void	sigquit(void)
{
	//ft_putstr_fd("", STDERR_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	//ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
}

void	shell_sigaction(int signo, siginfo_t *info, void *context)
{
	(void)context;
	if (signo == SIGINT)
		sigint(info->si_pid);
	else if (signo == SIGQUIT)
		sigquit();
}
