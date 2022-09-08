#include "minishell.h"
#include "executor.h"

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
		if (cur_cmd->cmd->type == CMD && check_cmdpath(sh, cur_cmd->cmd))
			sh->last_exit_value = 127;

		rredir = redirection(cur_cmd);

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
			if (rredir)
			{
				printf("rredir : %d\n", rredir);
				sh->last_exit_value = rredir;
				exit(rredir);
			}
			/* recv input from prev pipe/file/tty */
			dup2(cur_cmd->fd_in, STDIN_FILENO);
			if (cur_cmd->fd_in != STDIN_FILENO) //not first cmd
				close(cur_cmd->fd_in);

			//TODO_2 : argv 만들기 (filename word 구분)
			//argv
			//char *argv[] =
			//{
			//	cur_cmd->cmd->content,
			//	cur_cmd->cmd->next->content,
			//	NULL
			//};
			argv = make_arguments(cur_cmd);
			execve(cur_cmd->cmd->content, argv, NULL);
			free(argv);
				//find_env_value(sh->env, "PATH")); // should pass envp here
			// exit(1);
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
			else //표준입출력 정상복구?
			{
				close(pipeline[0]);
				close(pipeline[1]);
				dup2(stdin_dup, 0);
				dup2(stdout_dup, 1);
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
