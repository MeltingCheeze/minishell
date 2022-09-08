#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <sys/wait.h>

int g_is_heredoc;

static void	sigint(void)
{
	if (g_is_heredoc)
	{
		ft_putchar_fd('\0', STDOUT_FILENO);
		exit(130);
	}
	else
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	sigquit(void)
{
	//ft_putstr_fd("", STDERR_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	//ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler(int signo)
{
	if (signo == SIGINT)
		sigint();
	else if (signo == SIGQUIT)
		sigquit();
}

void	set_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
