#include "minishell.h"
#include "executor.h"
#include "builtin.h"
#include <sys/types.h> 
#include <sys/wait.h>

void	 child_process(t_sh *sh, t_script *cur_cmd, int *pipeline)
{
	char		**argv;
	char		*cmd_path;
	int			redir;
	t_builtin	builtin;

	redir = 0;
	argv = 0;
	redir = redirection(cur_cmd);
	if (redir)
		exit(redir);

	/* close input pipe */
	if (cur_cmd->next != NULL)
		close(pipeline[READ]);
	/* change input fd */
	dup2(cur_cmd->fd_in, STDIN_FILENO);
	if (cur_cmd->fd_in != STDIN_FILENO)
		close(cur_cmd->fd_in);

	/* change output fd */
	if (cur_cmd->fd_out > 1) // RD_OUT or RD_APPEND 존재 -> pipe보다 redir이 우선!
	{
		dup2(cur_cmd->fd_out, STDOUT_FILENO);
		close(cur_cmd->fd_out);
		close(pipeline[WRITE]);
	}
	else if (cur_cmd->next != NULL) // redir X, pipe O
	{
		dup2(pipeline[WRITE], STDOUT_FILENO);
		close(pipeline[WRITE]);
	} 

	argv = make_arguments(cur_cmd);
	builtin = is_builtin(cur_cmd->head);
	if (builtin)
		exit(execve_builtin(argv, sh, cur_cmd, builtin));
	cmd_path = cmd_to_path(sh, cur_cmd->head);
	if (execve(cmd_path, argv, sh->env_info.envp) < 0)
	{
		if (argv && !argv[0])
			exit(EXIT_SUCCESS);
		exit(execute_error(argv[0])); // g_last_exit_value = execute_error(argv[0]);;
	}
}

void	parent_process(t_script *cur_cmd, int *pipeline, int *std_dup)
{
	if (cur_cmd->next != NULL)
	{
		close(pipeline[WRITE]);

		dup2(pipeline[READ], STDIN_FILENO);
		close(pipeline[READ]);
	}
	else
	{
		dup2(std_dup[0], STDIN_FILENO);
		dup2(std_dup[1], STDOUT_FILENO);
		close(std_dup[0]);
		close(std_dup[1]);
	}
}

static void	wait_child(t_sh *sh)
{
	t_script *curr;
	int		statloc;

	curr = sh->script;
	while (curr)
	{
		wait(&statloc);
		g_last_exit_value = WEXITSTATUS(statloc);
		curr = curr->next;
	}
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

	dup2(cur_cmd->fd_in, STDIN_FILENO);
	if (cur_cmd->fd_in != STDIN_FILENO)
		close(cur_cmd->fd_in);

	dup2(cur_cmd->fd_out, STDOUT_FILENO);
	if (cur_cmd->fd_out != STDOUT_FILENO)
		close(cur_cmd->fd_out);

	argv = make_arguments(cur_cmd);
	builtin = is_builtin(cur_cmd->head);
	rvalue = execve_builtin(argv, sh, cur_cmd, builtin);
	free(argv);
	dup2(std_dup[0], STDIN_FILENO);
	dup2(std_dup[1], STDOUT_FILENO);
	close(std_dup[0]);
	close(std_dup[1]);
	g_last_exit_value = rvalue;
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
	return (rvalue);
}

int execute(t_sh *sh)
{
	t_script	*cur_cmd;
	pid_t		pid;
	int			pipeline[2];
	int 		std_dup[2];

	signal(SIGINT, &signal_execute);
	signal(SIGQUIT, &signal_execute);
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_on);

	std_dup[0] = dup(0);
	std_dup[1] = dup(1);

	cur_cmd = sh->script;
	g_last_exit_value = 0;
	
	if (!sh->multi_cmd_flag && is_builtin(cur_cmd->head))
		return (only_builtin(sh, cur_cmd, std_dup));
	
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
	
	wait_child(sh);
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
	return (0);
}

