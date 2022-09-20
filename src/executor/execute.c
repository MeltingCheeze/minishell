#include "minishell.h"
#include "executor.h"
#include "builtin.h"
#include <sys/types.h> 
#include <sys/wait.h>


void	 child_process(t_sh *sh, t_script *cur_cmd, int *pipeline)
{
	char		**argv;
	char		*cmd_path;
	t_builtin	builtin;
	int			redir;

	redir = 0;
	redir = redirection(cur_cmd);
	if (redir)
		exit(redir);

	if (cur_cmd->fd_out > 1) // RD_OUT or RD_APPEND 존재 -> pipe보다 redir이 우선!
	{
		dup2(cur_cmd->fd_out, STDOUT_FILENO);
		close(cur_cmd->fd_out);
		// close(pipeline[WRITE]);
	}
	else if (cur_cmd->next != NULL) // redir X, pipe O
	{
		/* close input pipe -> no use */
		close(pipeline[READ]);	

		/* change output fd */
		dup2(pipeline[WRITE], STDOUT_FILENO);
		close(pipeline[WRITE]);
	}
	/* recv input from prev pipe/file/tty */
	dup2(cur_cmd->fd_in, STDIN_FILENO);
	if (cur_cmd->fd_in != STDIN_FILENO) //not first cmd
		close(cur_cmd->fd_in);
	
	argv = make_arguments(cur_cmd);
	cmd_path = cmd_to_path(sh, cur_cmd->head);
	builtin = is_builtin(cur_cmd->head);
	if (builtin)
		exit(execve_builtin(argv, sh, cur_cmd, builtin));

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
		/* close output pipe -> no use */
		close(pipeline[WRITE]);

		/* change input fd */
		dup2(pipeline[READ], STDIN_FILENO);
		// if (pipeline[READ] != STDIN_FILENO)
		// 	close(pipeline[READ]);
		if (cur_cmd->fd_in != STDIN_FILENO) //not first cmd
			close(cur_cmd->fd_in);
	}
	else //표준입출력 원상복구?
	{
		close(pipeline[0]);
		close(pipeline[1]);
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
		// printf("=======g_last_exit_value : %d\n=======", g_last_exit_value);
		curr = curr->next;
	}
}

int execute(t_sh *sh)
{
	t_script	*cur_cmd;
	int			pipeline[2];
	pid_t		pid;
	t_builtin	builtin;
	char		**argv;
	int 		std_dup[2];
	
	std_dup[0] = dup(0);
	std_dup[1] = dup(1);

	cur_cmd = sh->script;
	g_last_exit_value = 0;
	argv = 0;

	if (cur_cmd->next == NULL) 
	{
		int	rvalue;
		rvalue = 0;

		rvalue = redirection(cur_cmd);
		if (rvalue)
			return (rvalue);

		if (cur_cmd->fd_in != STDIN_FILENO)
		{
			dup2(cur_cmd->fd_in, STDIN_FILENO);
			close(cur_cmd->fd_in);
		}
		if (cur_cmd->fd_out != STDOUT_FILENO)
		{
			dup2(cur_cmd->fd_out, STDOUT_FILENO);
			close(cur_cmd->fd_out);
		}
		builtin = is_builtin(cur_cmd->head);
		if (builtin)
		{
			argv = make_arguments(cur_cmd);
			rvalue = execve_builtin(argv, sh, cur_cmd, builtin);
			dup2(std_dup[0], STDIN_FILENO);
			dup2(std_dup[1], STDOUT_FILENO);
			close(std_dup[0]);
			close(std_dup[1]);
			g_last_exit_value = rvalue;
			return (rvalue);	
		}
	}

	while (cur_cmd)
	{
		if (cur_cmd->next != NULL) //not last cmd
			pipe(pipeline);
		pid = fork();

		if (pid == 0)
			child_process(sh, cur_cmd, pipeline);
		else if (pid > 0)
			parent_process(cur_cmd, pipeline, std_dup);
		cur_cmd = cur_cmd->next;
		// if (cur_cmd)
		// 	cur_cmd->fd_in = pipeline[WRITE];
	}

	wait_child(sh);
	return (0);
}
