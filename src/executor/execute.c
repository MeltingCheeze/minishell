/* execute.c 파일에 redirection 추가하면서 수정하고있는 파일 */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"

int execve_builtin(char **argv, t_sh *sh, t_builtin builtin)
{
	int	rvalue;

	rvalue = 0;
	if (builtin == EXPORT)
		rvalue = builtin_export(argv, &sh->env_info);
	else if (builtin == ENV)
		rvalue = builtin_env(argv, &sh->env_info);
	else
		printf("need builtin function\n");
	return (rvalue);
}

int	arguments_vector(t_script *cur_cmd, char **argv)
{
	t_token *cur_token;
	int	i;

	i = 0;
	cur_token = cur_cmd->head;
	while (cur_token)
	{
		if (cur_token->type == CMD || cur_token->type == WORD)
		{
			argv[i] = cur_token->content;
			i++;
		}
		cur_token = cur_token->next;
	}
	argv[i] = NULL;


	i = 0;
	while (argv[i])
	{
		printf("%d: %s\n", i, argv[i]);
		i++;
	}

	return (0);
}

void	child_process(t_sh *sh, t_script *cur_cmd, int *pipeline)
{
	char		**argv; // 이거 수정됨
	char		*cmd;

	redirection(cur_cmd);
	// arguments_vector(cur_cmd, argv);

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
	// builtin = is_builtins(cur_cmd->head);
	// if (builtin)
	// 	exit(execve_builtin(argv, sh, builtin));
	cmd = cmd_to_path(sh, cur_cmd->head); //수정해줘
	if (execve(cmd, argv, sh->env_info.envp) < 0)
	{
		if (argv && !argv[0])
			exit(EXIT_SUCCESS); // `< a` 같은 경우
		execute_error(argv[0]);
		exit(EXIT_FAILURE);
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

int execute(t_sh *sh)
{
	t_script	*cur_cmd;
	int			pipeline[2];
	pid_t		pid;
	t_builtin	builtin;
	char		**argv; // 이거 수정됨
	// char		*argv[10]; //배열 크기 어떻게 설정하는게 좋을지...
	int 		std_dup[2];
	
	std_dup[0] = dup(0);
	std_dup[1] = dup(1);

	cur_cmd = sh->script;
	sh->last_exit_value = 0;
	argv = 0;




	if (cur_cmd->next == NULL) // 이거 파이프 없이, 명령어 한번 실행할때 builtin 실행 (builtin 은 exit 없이, return만 해요!)
	{
		builtin = is_builtins(cur_cmd->head);
		if (builtin)
		{
			argv = make_arguments(cur_cmd);
			return (execve_builtin(argv, sh, builtin));
		}
	}
	while (cur_cmd)
	{
		//TODO_1 : 일단 여기서 cmdpath_expansion

		/* create pipe */
		if (cur_cmd->next != NULL) //not last cmd
			pipe(pipeline);

		/* fork */
		pid = fork();

		/* child process -> WRITE only */
		if (pid == 0)
		{
			child_process(sh, cur_cmd, pipeline);
		}
		/* parent process -> READ only */
		else if (pid > 0)
		{
			parent_process(cur_cmd, pipeline, std_dup);
		}
		cur_cmd = cur_cmd->next;
		if (cur_cmd)
			cur_cmd->fd_in = pipeline[WRITE]; //next cmd fd_in = current cmd fd_out
	}

	cur_cmd = sh->script;
	while (cur_cmd)
	{
		wait(NULL);
		cur_cmd = cur_cmd->next;
	}
	return (0);
}
