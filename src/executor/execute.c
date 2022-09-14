#include "minishell.h"
#include "executor.h"

int execve_builtin(void)
{
	printf("need builtin function\n");
	exit(1);
}

void execute(t_sh *sh)
{
	t_script	*cur_cmd;
	int			pipeline[2];
	pid_t		pid;
	char		**argv;
	int			rredir; // return value of redir (SIGINT -> 130)
	#define READ 0
	#define WRITE 1

	int stdin_dup = dup(0);
	int stdout_dup = dup(1);

	cur_cmd = sh->script;
	sh->last_exit_value = 0;
	argv = 0;
	while (cur_cmd)
	{
		/* check_cmdpath (is built_in or not) */
		// exeve - it will find its path from envp

		rredir = redirection(sh->env_info.head, cur_cmd);

		/* create pipe */
		if (cur_cmd->next != NULL) //not last cmd
			pipe(pipeline);

		/* fork */
		pid = fork();

		/* child process -> WRITE only */
		if (pid == 0)
		{
			if (cur_cmd->next != NULL)
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
			if (rredir)
			{
				printf("rredir : %d\n", rredir);
				sh->last_exit_value = rredir;
				exit(EXIT_FAILURE);
			}
			else if (cur_cmd->cmd->type != CMD)
				exit(EXIT_SUCCESS);
			argv = make_arguments(cur_cmd);
			if (is_builtins(cur_cmd->cmd->content))
				execve_builtin();
			cmd_to_path(sh, cur_cmd->cmd);
			if (execve(cur_cmd->cmd->content, argv, sh->env_info.envp) < 0)
			{
				execute_error(argv[0]);
				exit(EXIT_FAILURE);
			}
		}
		/* parent process -> READ only */
		else if (pid > 0)
		{
			if (cur_cmd->next != NULL)
			{
				/* close output pipe -> no use */
				close(pipeline[WRITE]);

				/* change input fd */
				dup2(pipeline[READ], STDIN_FILENO);
				if (cur_cmd->fd_in != STDIN_FILENO) //not first cmd
					close(cur_cmd->fd_in);
			}
			else //표준입출력 원상복구?
			{
				close(pipeline[0]);
				close(pipeline[1]);
				dup2(stdin_dup, STDIN_FILENO);
				dup2(stdout_dup, STDOUT_FILENO);
				close(stdin_dup);
				close(stdout_dup);
			}
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
}
