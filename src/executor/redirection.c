#include "executor.h"
#include <fcntl.h>

static int rd_in(char *filepath)
{
	int fd;

	fd = open(filepath, O_RDONLY, 0644);
	// if (fd == -1)
	//	return (file_not_found_print("<cmd>", filepath));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int rd_out(char *filepath)
{
	int fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (fd == -1)
	//	return (error(filepath));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int rd_append(char *filepath)
{
	int fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// if (fd == -1)
	//	return (error(filepath));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int heredoc(int herepipe[2], char *eof)
{
	int rvalue;

	rvalue = heredoc_execute(herepipe, eof);
	if (rvalue)
		close(herepipe[0]);
	else
	{
		dup2(herepipe[0], STDIN_FILENO);
		close(herepipe[0]);
	}
	close(herepipe[1]);
	return (rvalue);
}

int redirection(t_script *script)
{
	t_token *cur_token;
	int rvalue;

	rvalue = 0;
	cur_token = script->cmd;
	while (cur_token && !rvalue)
	{
		// cur_token->next->type == FILENAME -> lexer 에서 처리됨
		if (cur_token->type == RD_IN)
			rvalue = rd_in(cur_token->next->content);
		// cur_cmd->fd_in = open(cur_token->next->content, O_RDONLY, 0644);
		else if (cur_token->type == RD_OUT)
			rvalue = rd_out(cur_token->next->content);
		else if (cur_token->type == RD_APPEND && cur_token->next->type == FILENAME)
			rvalue = rd_append(cur_token->next->content);
		else if (cur_token->type == RD_HEREDOC && cur_token->next->type == FILENAME)
		{
			pipe(script->herepipe);
			rvalue = heredoc(script->herepipe, cur_token->next->content);
		}
		cur_token = cur_token->next;
	}
	return (rvalue);
}
