/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:58:15 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 20:09:19 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtin.h"
#include "redirection.h"
#include <sys/types.h> 
#include <sys/wait.h>

static	void	child_dup_fd(t_script *cur_cmd, int *pipeline)
{
	if (cur_cmd->next != NULL)
		close(pipeline[READ]);
	dup2(cur_cmd->fd_in, STDIN_FILENO);
	if (cur_cmd->fd_in != STDIN_FILENO)
		close(cur_cmd->fd_in);
	if (cur_cmd->fd_out > 1)
	{
		dup2(cur_cmd->fd_out, STDOUT_FILENO);
		close(cur_cmd->fd_out);
		close(pipeline[WRITE]);
	}
	else if (cur_cmd->next != NULL)
	{
		dup2(pipeline[WRITE], STDOUT_FILENO);
		close(pipeline[WRITE]);
	}
}

void	child_process(t_sh *sh, t_script *cur_cmd, int *pipeline)
{
	char		**argv;
	char		*cmd_path;
	int			redir;
	t_builtin	builtin;

	redir = 0;
	argv = 0;
	redir = redirection(cur_cmd);
	if (redir)
		exit(EXIT_FAILURE);
	child_dup_fd(cur_cmd, pipeline);
	argv = make_arguments(cur_cmd);
	if (*argv == 0)
		exit(EXIT_SUCCESS);
	builtin = is_builtin(cur_cmd->head);
	if (builtin)
		exit(execve_builtin(argv, sh, builtin));
	cmd_path = cmd_to_path(sh, cur_cmd->head);
	if (execve(cmd_path, argv, sh->env_info.envp) < 0)
	{
		free(cmd_path);
		if (argv && !argv[0])
			exit(EXIT_SUCCESS);
		exit(execute_error(argv[0]));
	}
}
