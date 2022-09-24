/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:55:09 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 16:44:41 by chaejkim         ###   ########.fr       */
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
	int			rvalue;
	char		**argv;

	rvalue = 0;
	rvalue = redirection(cur_cmd);
	if (rvalue)
	{
		tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
		return (rvalue);
	}
	builtin_dup_fd(cur_cmd);
	argv = make_arguments(cur_cmd);
	builtin = is_builtin(cur_cmd->head);
	rvalue = execve_builtin(argv, sh, builtin);
	free(argv);
	dup2(std_dup[0], STDIN_FILENO);
	dup2(std_dup[1], STDOUT_FILENO);
	close(std_dup[0]);
	close(std_dup[1]);
	g_last_exit_value = rvalue;
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
	return (rvalue);
}

static void	wait_child(t_sh *sh)
{
	t_script	*curr;
	int			statloc;

	curr = sh->script;
	while (curr)
	{
		wait(&statloc);
		g_last_exit_value = WEXITSTATUS(statloc);
		curr = curr->next;
	}
}

static	void	pipe_and_fork(t_sh *sh, int	*std_dup)
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
			child_process(sh, cur_cmd, pipeline);
		else if (pid > 0)
			parent_process(cur_cmd, pipeline, std_dup);
		cur_cmd = cur_cmd->next;
	}
}

int	execute(t_sh *sh)
{
	int			std_dup[2];

	signal(SIGINT, &signal_execute);
	signal(SIGQUIT, &signal_execute);
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_on);
	std_dup[0] = dup(0);
	std_dup[1] = dup(1);
	if (!sh->multi_cmd_flag && is_builtin(sh->script->head))
		return (only_builtin(sh, sh->script, std_dup));
	pipe_and_fork(sh, std_dup);
	wait_child(sh);
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
	return (0);
}
