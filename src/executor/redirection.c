#include "minishell.h"

int	redirection(t_script *cur_cmd)
{
	t_token *cur_token;
	cur_token = cur_cmd->cmd;
	while (cur_token)
	{
		if (cur_token->type == RD_IN && cur_token->next->type == WORD) //->FILENAME으로 수정 필요?
		{
			cur_cmd->fd_in = open(cur_token->next->content, O_RDONLY, 0644);
			if (cur_cmd->fd_in < 0)
				return (-1); //redir 실패시 에러 or 건너뛰기???
		}
		else if (cur_token->type == RD_OUT && cur_token->next->type == WORD)
		{
			cur_cmd->fd_out = open(cur_token->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0744);
			if (cur_cmd->fd_out < 0)
				return (-1);
		}
		else if (cur_token->type == RD_APPEND && cur_token->next->type == WORD)
		{
			cur_cmd->fd_out = open(cur_token->next->content, O_WRONLY | O_CREAT | O_APPEND, 0744);
			if (cur_cmd->fd_out < 0)
				return (-1);
		}
		else if (cur_token->type == RD_HEREDOC && cur_token->next->type == WORD)
		{

		}
		cur_token = cur_token->next;
	}
	return (0);
}
