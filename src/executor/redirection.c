#include "minishell.h"

// O_WRONLY | O_CREAT | O_TRUNC - 쓰기 전용으로 열 때, 파일이 없는 경우 내용을 모두 지우고 파일의 길이를 0으로 변경

// void	redirection(t_sh *sh)
// {
// 	t_script *cur_cmd;
// 	t_token *cur_token;

// 	cur_cmd = sh->script;
// 	cur_token = cur_cmd->cmd;
// 	int	new_fd;
// 	while (cur_cmd)
// 	{
// 		while (cur_token)
// 		{
// 			if (cur_token->type == RD_OUT)
// 			{
// 				cur->token->next->type = FILENAME;
// 				new_fd = open(cur_token->next->content, O_RDWR | O_CREAT);
// 				dup2(new_fd ,cur_cmd->fd_in);
// 			}
// 			else if (cur_token->type == RD_APPEND)
// 			{
// 				cur_cmd->fd_out;

// 			}
// 			else if (cur_token->type == RD_IN) 
// 			{
// 				cur_cmd->fd_in;

// 			}
// 			else if (cur_token->type == RD_HEREDOC)
// 			{
// 				cur_cmd->fd_in;
// 			}
// 			cur_token = cur_token->next;
// 		}
// 		cur_cmd = cur_cmd->next;
// 	}
// }

void	redirection(t_token *token, t_script *cmd)
{
	if (token->type == RD_IN)
	{
		fd = open("test.txt", O_RDONLY);
	}
}