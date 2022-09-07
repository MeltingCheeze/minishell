/* execute.c 파일에 redirection 추가하면서 수정하고있는 파일 */

#include "minishell.h"

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
			//////////* REDIRECTION */////////
			t_token *cur_token;
			cur_token = cur_cmd->cmd;
			while (cur_token)
			{
				if (cur_token->type == RD_IN && cur_token->next->type == WORD) //->FILENAME으로 수정 필요?
				{
					cur_cmd->fd_in = open(cur_token->next->content, O_RDONLY);
					if (cur_cmd->fd_in < 0)
						return (-1); //redir 실패시 에러 or 건너뛰기???
				}
				else if (cur_token->type == RD_OUT && cur_token->next->type == WORD)
				{
					cur_cmd->fd_out = open(cur_token->next->content, O_WRONLY | O_CREAT | O_TRUNC);
					if (cur_cmd->fd_out < 0)
						return (-1);
				}
				else if (cur_token->type == RD_APPEND && cur_token->next->type == WORD)
				{
					cur_cmd->fd_out = open(cur_token->next->content, O_WRONLY | O_CREAT | O_APPEND);
					if (cur_cmd->fd_out < 0)
						return (-1);
				}
				else if (cur_token->type == RD_HEREDOC && cur_token->next->type == WORD)
				{
				}
				cur_token = cur_token->next;
			}
			/////////////////////////////////

			if (cur_cmd->fd_out) // RD_OUT or RD_APPEND 존재 -> pipe보다 redir이 우선!
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
			//TODO_2 : argv 만들기 (filename word 구분)
			char *argv[] = {
				cur_cmd->cmd->content,
				cur_cmd->cmd->next->content,
				NULL
			};
			execve(cur_cmd->cmd->content, argv, NULL); // should pass envp here
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