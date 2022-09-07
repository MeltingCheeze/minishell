#include "minishell.h"

extern char** environ;

void execute(t_sh *sh)
{
	t_script	*cur_cmd;
	int			pipeline[2];
	pid_t		pid;
	#define READ 0
	#define WRITE 1
	
	int stdin_dup = dup(0);
	int stdout_dup = dup(1);

	cur_cmd = sh->script;
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
			//////////* RD_IN */////////
			t_token *cur_token;
			cur_token = cur_cmd->cmd;
			while (cur_token)
			{
				if (cur_token->type == RD_IN)
				{
					// printf("redir\n");
					int	fd;
					fd = open(cur_token->next->content, O_RDONLY);
					printf("fd : %d\n", fd);
					cur_cmd->fd_in = fd;
				}
				cur_token = cur_token->next;
			}
			/////////////////////////////

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
			//TODO_2 : argv 만들기 (filename word 구분)
			//TODO_3 : redirection
			// 근데 리다이렉션 해서 만든 값을 어디다 저장하지.. -> script.fd 여기다가? 파이프로? -> disccution...
			// 히코야 모르겠닼ㅋㅋㅋㅋㅋㅋㅋㅋ 이것저것 테스트해보고 disccution 에 올릴게
			char *argv[] = {
				cur_cmd->cmd->content,
				cur_cmd->cmd->next->content,
				NULL
			};
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