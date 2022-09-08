#include "minishell.h"
#include "executor.h"

extern char** environ;

void execute(t_sh *sh)
{
	t_script	*cur_cmd;
	int			pipeline[2];
	pid_t		pid;
	int			rheredoc; // return value of heredoc (SIGINT -> 130)
	#define READ 0
	#define WRITE 1

	int stdin_dup = dup(0);
	int stdout_dup = dup(1);

	cur_cmd = sh->script;
	while (cur_cmd)
	{
		//heredoc check
		pipe(cur_cmd->herepipe); // 이거 부터가 문제인듯.. 근데 어떻게 해결해야 할지 모르겠다..
		rheredoc = heredoc(cur_cmd);

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
			if (rheredoc == 130)
			{
				sh->last_exit_value = 130;
				exit(130);
			}
			else if (rheredoc == 0) // heredoc 성공적
			{
				dup2(cur_cmd->herepipe[0], cur_cmd->fd_in);
				close(cur_cmd->herepipe[0]);
				dup2(cur_cmd->herepipe[1], STDOUT_FILENO);
				close(cur_cmd->herepipe[1]);
			}
			char *argv[] =
			{
				cur_cmd->cmd->content,
				cur_cmd->cmd->next->content,
				NULL
			};
			if (!ft_strcmp(cur_cmd->cmd->next->content, "<<"))
				argv[1] = 0;
			execve(cur_cmd->cmd->content, argv, environ); // should pass envp here
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
