#include "executor.h"
#include <fcntl.h>
#include <stdio.h> //test

static int	rd_in(char *fname, int *infile)
{
	int	fd;

	fd = open(fname, O_RDONLY, 0644);
	if (fd == -1)
		return (open_error(fname));
	dup2(fd, STDIN_FILENO);
	close(fd);
	*infile = fd;
	return (0);
}

static int	rd_out(char *fname)
{
	int	fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (open_error(fname));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	rd_append(char *fname)
{
	int	fd;

	fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (open_error(fname));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

static int	heredoc(t_env *env, char *eof, int herecnt, int *infile)
{
	int	herepipe[2];
	int	rvalue;

	pipe(herepipe);
	rvalue = heredoc_execute(env, herepipe, eof);
	if (rvalue || herecnt)
		close(herepipe[0]);
	else
	{
		dup2(herepipe[0], STDIN_FILENO);
		close(herepipe[0]);
		*infile = herepipe[0];
	}
	close(herepipe[1]);
	return (rvalue);
}

int	redirection(t_env *env, t_script *script, int *infile)
{
	t_token	*cur_token;
	int		rvalue;
	int		herecnt;

	rvalue = 0;
	cur_token = script->cmd;
	herecnt = script->herecnt;
	while (cur_token && !rvalue)
	{
		if (cur_token->type == RD_IN)
			rvalue = rd_in(cur_token->next->content, infile);
		else if (cur_token->type == RD_OUT)
			rvalue = rd_out(cur_token->next->content);
		else if (cur_token->type == RD_APPEND)
			rvalue = rd_append(cur_token->next->content);
		else if (cur_token->type == RD_HEREDOC)
			rvalue = heredoc(env, cur_token->next->content, --herecnt, infile);
		cur_token = cur_token->next;
	}
	return (rvalue);
}
