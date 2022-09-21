#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <termios.h>

static void	sig_int(void)
{
	g_last_exit_value = 1;
	ft_putstr_fd("minishell$ ", STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sig_quit(void)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	signal_handler(int signo)
{
	if (signo == SIGINT) // ctrl + 'C'
		sig_int();
	else if (signo == SIGQUIT) // ctrl + '\'
		sig_quit();
	// else if (signo == SIGTERM) // ctrl + 'D'
	// 	sigterm();
}

void	set_signal()
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	// signal(SIGTERM, &signal_handler);
}

