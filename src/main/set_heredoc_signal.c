#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

int	g_last_exit_value;

static void	heredoc_sigint(void)
{
	g_last_exit_value = 130;
	ft_putchar_fd('\0', STDOUT_FILENO);
	exit(130);
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

static void	heredoc_signal_handler(int signo)
{
	if (signo == SIGINT)
		heredoc_sigint();
	else if (signo == SIGQUIT)
		sigquit();
}

void	set_heredoc_signal(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, heredoc_signal_handler);
}
