#include "minishell.h"

extern char** environ;

void execute(t_sh *sh)
{
	t_script	*cur_cmd;
	int			pipeline[2];
	pid_t		pid;
	#define READ 0
	#define WRITE 1

	cur_cmd = sh->script;
	while (cur_cmd)
	{
		/* create pipe */
		if (cur_cmd->next != NULL) //not last cmd
		{
			pipe(pipeline);
			printf("<pipe> %d %d\n", pipeline[0], pipeline[1]);
		}
		/* fork */
		pid = fork();

		/* child process -> WRITE only */
		if (pid == 0)
		{
			if (cur_cmd->next != NULL)
			{
				//close input pipe -> no use
				close(pipeline[READ]);	
				//pass output to pipeline/tty
				dup2(pipeline[WRITE], STDOUT_FILENO);
				close(pipeline[WRITE]);
			}
			// recv input from prev pipe/file/tty
			dup2(cur_cmd->fd_in, STDIN_FILENO);
			if (cur_cmd->fd_in != STDIN_FILENO)
				close(cur_cmd->fd_in);
			
			char *argv[] = {
				cur_cmd->cmd->content,
				NULL
			};
			printf("cmd : %s, in_fd : %d\n", cur_cmd->cmd->content, cur_cmd->fd_in);
			execve(cur_cmd->cmd->content, argv, environ); // should pass envp here
			exit(1);
		}
		/* parent process -> READ only */
		else if (pid > 0)
		{
			//close output pipe -> no use
			if (cur_cmd->next != NULL)
				close(pipeline[WRITE]);
			//
			dup2(pipeline[READ], STDIN_FILENO);
			if (cur_cmd->fd_in != STDIN_FILENO)
				close(cur_cmd->fd_in);
			// cur_cmd->fd_in = pipeline[READ];
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
