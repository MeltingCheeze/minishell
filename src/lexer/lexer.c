#include "parser.h"
#include "libft.h"
#include <stdio.h> // 나중에 지우기

static void	check_type(t_token *line)
{
	t_type	t;

	t = PIPE;
	//printf("ttt : %d\n", (int)t);
	while (line)
	{
		if (ft_strcmp(line->content, "|") == 0)
		{
			line->type = PIPE;
		}
		else  if (ft_strcmp(line->content, "<") == 0)
		{
			line->type = RD_IN;
		}
		else  if (ft_strcmp(line->content, ">") == 0)
		{
			line->type = RD_OUT;
		}
		else  if (ft_strcmp(line->content, "<<") == 0)
		{
			line->type = RD_HEREDOC;
		}
		else  if (ft_strcmp(line->content, ">>") == 0)
		{
			line->type = RD_APPEND;
		}
		else
		{
			line->type = WORD;
		}
		if (line->next)
			line = line->next;
		else
			break;
	}
}

static int	 check_cmd(t_token *line)
{
	if (line->type == WORD)
		line->type = CMD;
	while (line->next) // 이거 세그 폴트때매 일단 수정
	{
		if (line->type == PIPE && line->next->type == WORD)
			line->next->type = CMD;
		line = line->next;
	}
	if (line->type == PIPE)
		return (-1);
		//syntax error
	return (0);
}

static int	check_gram(t_token *line)
{
	if (line->type == PIPE) //first token
		return (-1);
	while (line)
	{
		if (line->type == CMD && line->next != NULL) //cmd
		{
			if (line->next->type == CMD)
				return (-1);
		}
		else if (line->type == WORD && line->next != NULL) //word
		{
			if (line->next->type == CMD)
				return (-1);
		}
		else if (line->type == PIPE && line->next != NULL) //pipe
		{
			if (line->next->type == WORD)
				return (-1);
			else if (line->next->type == PIPE)
				return (-1);
		}
		else if (line->type >= RD_IN && line->next != NULL) //redir
		{
			if (line->next->type != WORD)
				return (-1);
		}
		if (!line->next && (line->type >= RD_IN || line->type == PIPE)) //last token
			return (-1);
		line = line->next;
	}
	return (0);
}

int	lexcial_analyze(t_token *line)
{
	check_type(line);
	if (check_cmd(line) || check_gram(line))
		return (-1);
	return (0);
}
