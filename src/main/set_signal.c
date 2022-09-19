#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>

// static void	sigint(void)
// {
// 	g_last_exit_value = 1;
// 	// printf("\b\b\n");
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }



static void	sigquit(void)
{
	//ft_putstr_fd("", STDERR_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	//ft_putchar_fd('\n', STDERR_FILENO);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigterm(void)
{
	ft_putstr_fd("sigterm catched!!\n", STDERR_FILENO);
}

static void	signal_handler(int signo)
{
	// if (signo == SIGINT) // ctrl + 'C'
	// 	sigint();
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			// ft_putstr_fd("\n\b\b", STDOUT_FILENO);
			ft_putstr_fd("minishell$   \b\b\n", STDOUT_FILENO);
			// ft_putstr_fd("", STDOUT_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_last_exit_value = 1;
		}
		else
		{
			ft_putstr_fd("fdfd$ ", STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	else if (signo == SIGQUIT) // ctrl + '\'
		sigquit();
	else if (signo == SIGTERM) // ctrl + 'D'
		sigterm();
}

void	set_signal()
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	signal(SIGTERM, &signal_handler);
}

// void		signal_handler(int signo)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = waitpid(-1, &status, WNOHANG);
// 	if (signo == SIGINT)
// 	{
// 		if (pid == -1)
// 		{
// 			g_last_exit_value = 1;
// 			ft_putstr_fd("\b\b \b\b\n", STDOUT_FILENO);
// 			ft_putstr_fd("minishell$ ", STDIN_FILENO);
// 		}
// 		else
// 			ft_putchar_fd('\n', STDOUT_FILENO);
// 	}
// 	else if (signo == SIGQUIT)
// 	{
// 		if (pid == -1)
// 			ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
// 		else
// 			ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
// 	}
// }

// void		set_signal(void)
// {
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, signal_handler);
// }
