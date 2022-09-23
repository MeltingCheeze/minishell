/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:27:02 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:43:31 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	terminal_setting(t_sh *sh)
{
	tcgetattr(STDOUT_FILENO, &sh->echo_on);
	tcgetattr(STDOUT_FILENO, &sh->echo_off);
	sh->echo_on.c_lflag |= (ECHOCTL);
	sh->echo_off.c_lflag &= (~ECHOCTL);
}

void	signal_readline(int signo)
{
	if (signo == SIGINT)
	{
		g_last_exit_value = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_execute(int signo)
{
	if (signo == SIGINT)
		printf("\n");
	else if (signo == SIGQUIT)
		printf("Quit: 3\n");
}

void	signal_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_last_exit_value = 1;
		printf("\n");
		exit(g_last_exit_value);
	}
}
