#include "minishell.h"
#include "executor.h"
#include "builtins.h"

int	g_last_exit_value;

int execve_builtin(char **argv, t_sh *sh, t_script *cur_cmd, t_builtin builtin)
{
	int	rvalue;

	rvalue = 0;
	if (builtin == EXPORT)
		rvalue = builtin_export(argv, &sh->env_info);
	else if (builtin == ENV)
		rvalue = builtin_env(argv, &sh->env_info);
	else if (builtin == UNSET)
		rvalue = builtin_unset(argv, &sh->env_info);
	else if (builtin == ECHO)
		rvalue = builtin_echo(argv, cur_cmd);
	else if (builtin == PWD)
		rvalue = builtin_pwd(cur_cmd);
	else if (builtin == CD)
		rvalue = builtin_cd(argv, &sh->env_info);
	else if (builtin == EXIT)
		rvalue = builtin_exit(argv, sh);
	else
		printf("need builtin function\n");
	return (rvalue);
}

void	 child_process(t_sh *sh, t_script *cur_cmd, int *pipeline)
{
	char		**argv; // 이거 수정됨
	char		*cmd;
	t_builtin	builtin;

	redirection(cur_cmd);
	
	if (cur_cmd->fd_out > 1) // RD_OUT or RD_APPEND 존재 -> pipe보다 redir이 우선!
	{
		dup2(cur_cmd->fd_out, STDOUT_FILENO);
		close(cur_cmd->fd_out);
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
	cmd = cmd_to_path(sh, cur_cmd->head);
	builtin = is_builtins(cur_cmd->head);
	if (builtin)
		exit(execve_builtin(argv, sh, cur_cmd, builtin));

	if (execve(cmd, argv, sh->env_info.envp) < 0) // 인자로 "" 들어왔을때 ERROR 발생해서 일단 주석처리함 
	{
		if (*cmd || (argv && !argv[0]))
			exit(EXIT_SUCCESS); // `< a` 같은 경우
		exit(execute_error(argv[0])); // g_last_exit_value = execute_error(argv[0]);
		// exit(EXIT_FAILURE);
	}
}

void	parent_process(t_script *cur_cmd, int *pipeline, int *std_dup)
{
	if (cur_cmd->next != NULL)
	{
		/* close output pipe -> no use */
		close(pipeline[WRITE]);

		// /* change input fd */
		dup2(pipeline[READ], STDIN_FILENO);
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

	curr = sh->script;
	while (curr)
	{
		wait(NULL);
		curr = curr->next;
	}
}

int execute(t_sh *sh)
{
	t_script	*cur_cmd;
	int			pipeline[2];
	pid_t		pid;
	t_builtin	builtin;
	char		**argv; // 이거 수정됨
	int 		std_dup[2];
	
	std_dup[0] = dup(0);
	std_dup[1] = dup(1);

	cur_cmd = sh->script;
	g_last_exit_value = 0;
	argv = 0;

	// 이거 파이프 없이, 명령어 한번 실행할때 builtin 실행 (builtin 은 exit 없이, return만 해요!)
	if (cur_cmd->next == NULL) 
	{
		int	rvalue;
		if (redirection(cur_cmd) < 0)
			return (-1);
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
		builtin = is_builtins(cur_cmd->head);
		if (builtin)
		{
			argv = make_arguments(cur_cmd);
			rvalue = execve_builtin(argv, sh, cur_cmd, builtin);
			dup2(std_dup[0], STDIN_FILENO);
			dup2(std_dup[1], STDOUT_FILENO);
			close(std_dup[0]);
			close(std_dup[1]);
			return (rvalue);	
		}
	}

	while (cur_cmd)
	{
		//TODO_1 : 일단 여기서 cmdpath_expansion

		if (cur_cmd->next != NULL) //not last cmd
			pipe(pipeline);
		pid = fork();

		if (pid == 0)
			child_process(sh, cur_cmd, pipeline);
		else if (pid > 0)
			parent_process(cur_cmd, pipeline, std_dup);
		cur_cmd = cur_cmd->next;
		if (cur_cmd)
			cur_cmd->fd_in = pipeline[WRITE]; //next cmd fd_in = current cmd fd_out
	}

	wait_child(sh);
	return (0);
}
