#include "parser.h"
#include "libft.h"
#include <stdio.h> // 나중에 지우기

static void	check_type(t_token *token)
{
	t_token *curr;

	curr = token;
	while (curr)
	{
		if (ft_strcmp(curr->content, "|") == 0)
		{
			curr->type = PIPE;
		}
		else  if (ft_strcmp(curr->content, "<") == 0)
		{
			curr->type = RD_IN;
		}
		else  if (ft_strcmp(curr->content, ">") == 0)
		{
			curr->type = RD_OUT;
		}
		else  if (ft_strcmp(curr->content, "<<") == 0)
		{
			curr->type = RD_HEREDOC;
		}
		else  if (ft_strcmp(curr->content, ">>") == 0)
		{
			curr->type = RD_APPEND;
		}
		else
		{
			curr->type = WORD;
		}
		if (curr->next)
			curr = curr->next;
		else
			break;
	}
}

static int	 check_cmd_and_filename(t_token *token)
{
	t_token *curr;

	curr = token;
	if (curr->type == WORD) //first cmd
		curr->type = CMD;
	while (curr->next) // 이거 세그 폴트때매 일단 수정
	{
		if (curr->type == PIPE && curr->next->type == WORD)
			curr->next->type = CMD;
		if (curr->type > 3 && curr->next->type == WORD)
			curr->next->type = FILENAME;
		curr = curr->next;
	}
	if (curr->type == PIPE) //pipe로 끝나면...
		return (-1);
		//syntax error
	return (0);
}

static int	check_grammar(t_token *token)
{
	t_token *curr;

	curr = token;
	if (curr->type == PIPE) //first token
		return (-1);
	while (curr)
	{
		if (curr->type == CMD && curr->next != NULL) //cmd
		{
			if (curr->next->type == CMD)
				return (-1);
		}
		else if (curr->type == WORD && curr->next != NULL) //word
		{
			if (curr->next->type == CMD)
				return (-1);
		}
		else if (curr->type == PIPE && curr->next != NULL) //pipe
		{
			if (curr->next->type == WORD)
				return (-1);
			else if (curr->next->type == PIPE)
				return (-1);
		}
		else if (curr->type > 3 && curr->next != NULL) //redir
		{
			if (curr->next->type != FILENAME)
				return (-1);
		}
		if (!curr->next && (curr->type >= RD_IN || curr->type == PIPE)) //last token
			return (-1);
		curr = curr->next;
	}
	return (0);
}

int	lexcial_analyze(t_token *token)
{
	check_type(token);
	if (check_cmd_and_filename(token) || check_grammar(token))
	{
		printf("error -> lexer\n"); //에러처리 수정필요!!!
		return (-1);
	}
	return (0);
}
