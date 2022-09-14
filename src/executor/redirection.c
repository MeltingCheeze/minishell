#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int test()
{
	printf("abc\n");
	return (-1);
}

int	redirection(t_script *cur_cmd)
{
	t_token *cur_token;
	cur_token = cur_cmd->cmd;
	while (cur_token)
	{
		if (cur_token->type == RD_IN)
		{
			if (cur_cmd->fd_in != 0)
				close(cur_cmd->fd_in);
			cur_cmd->fd_in = open(cur_token->next->content, O_RDONLY, 0644);
			if (cur_cmd->fd_in < 0)
				// return (open_error(cur_token->next->content));
				return (-1); //redir 실패시 에러 or 건너뛰기???
		}
		else if (cur_token->type == RD_OUT)
		{
			if (cur_cmd->fd_out != 1)
				close(cur_cmd->fd_out);
			cur_cmd->fd_out = open(cur_token->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cur_cmd->fd_out < 0)
				return (-1);
		}
		else if (cur_token->type == RD_APPEND)
		{
			if (cur_cmd->fd_out != 1)
				close(cur_cmd->fd_out);
			cur_cmd->fd_out = open(cur_token->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cur_cmd->fd_out < 0)
				return (-1);
		}
		else if (cur_token->type == RD_HEREDOC)
		{
			char *line;
			char *doc;
			char *delimiter;

			delimiter = cur_token->next->content;
			while (1)
			{
				line = readline("> ");
				if (ft_strcmp(line, delimiter) != 0)
				{
					doc = ft_strjoin(doc, line);
					doc = ft_strjoin(doc, "\n");
				}
				else
					break ;
			}
			ft_putstr_fd(doc, cur_cmd->fd_in);
		}
		cur_token = cur_token->next;
	}
	return (0);
}
