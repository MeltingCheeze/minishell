/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:55:09 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 20:53:17 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtin.h"
#include "redirection.h"
#include <sys/types.h> 
#include <sys/wait.h>

static void	builtin_dup_fd(t_script *cur_cmd)
{
	dup2(cur_cmd->fd_in, STDIN_FILENO);
	if (cur_cmd->fd_in != STDIN_FILENO)
		close(cur_cmd->fd_in);
	dup2(cur_cmd->fd_out, STDOUT_FILENO);
	if (cur_cmd->fd_out != STDOUT_FILENO)
		close(cur_cmd->fd_out);
}

static int	only_builtin(t_sh *sh, t_script *cur_cmd, int *std_dup)
{
	t_builtin	builtin;
	int			result;
	char		**argv;

	result = 0;
	result = redirection(cur_cmd);
	if (result)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
		return (result);
	}
	builtin_dup_fd(cur_cmd);
	argv = make_arguments(cur_cmd);
	builtin = is_builtin(cur_cmd->head);
	result = execve_builtin(argv, sh, builtin);
	free(argv);
	dup2(std_dup[0], STDIN_FILENO);
	dup2(std_dup[1], STDOUT_FILENO);
	close(std_dup[0]);
	close(std_dup[1]);
	g_last_exit_value = result;
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
	return (result);
}

static int	wait_child(t_sh *sh, pid_t pid)
{
	t_script	*curr;
	int			statloc;
	int			last_stat;

	curr = sh->script;
	while (curr)
	{
		if (wait(&statloc) == pid)
			last_stat = statloc;
		curr = curr->next;
	}
	if (WIFEXITED(last_stat))
		return (WEXITSTATUS(last_stat));
	if (WIFSIGNALED(last_stat))
	{
		if (WTERMSIG(last_stat) == SIGQUIT)
			printf("Quit: 3\n");
		else
			printf("\n");
		return (WTERMSIG(last_stat) + 128);
	}
	return (WEXITSTATUS(last_stat));
}

static pid_t	pipe_and_fork(t_sh *sh, int	*std_dup)
{
	t_script	*cur_cmd;
	pid_t		pid;
	int			pipeline[2];

	cur_cmd = sh->script;
	while (cur_cmd)
	{
		if (cur_cmd->next != NULL)
			pipe(pipeline);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			close(std_dup[0]);
			close(std_dup[1]);
			child_process(sh, cur_cmd, pipeline);
		}
		else if (pid > 0)
		{
			parent_process(cur_cmd, pipeline, std_dup);
		}
		cur_cmd = cur_cmd->next;
	}
	return (pid);
}

int	execute(t_sh *sh)
{
	int			std_dup[2];

	if (g_last_exit_value)
		return (0);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_on);
	std_dup[0] = dup(0);
	std_dup[1] = dup(1);
	if (!sh->multi_cmd_flag && is_builtin(sh->script->head))
		return (only_builtin(sh, sh->script, std_dup));
	g_last_exit_value = wait_child(sh, pipe_and_fork(sh, std_dup));
	signal(SIGINT, signal_readline);
	signal(SIGQUIT, SIG_IGN);
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
	return (0);
}
