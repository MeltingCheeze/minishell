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

static int	check_filename(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (curr->type > 3 && curr->next && curr->next->type == WORD)
			curr->next->type = FILENAME;
		curr = curr->next;
	}
	return (0);
}

static int	check_cmd(t_token *token)
{
	t_token	*curr;

	curr = token;

	while (curr && curr->type != WORD) //first cmd
	{
		curr = curr->next;
	}
	if (curr == NULL)
		return (0);
	curr->type = CMD;

	while (curr)
	{
		if (curr->type == PIPE)
		{
			while (curr->type != WORD)
			{
				if (curr->next)
					curr = curr->next;
				else
					return (0);
			}
			curr->type = CMD;
		}
		if (curr->next)
			curr = curr->next;
		else
			break ;
		// printf("%s : %u\n", curr->content, curr->type);
	}
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
	if (check_filename(token) < -1)
	{
		printf("lexer error -> check_filename\n"); //나중에 삭제!!!
		return (-1);
	}
	if (check_cmd(token) < -1)
	{
		printf("lexer error -> check_cmd\n"); //나중에 삭제!!!
		return (-1);
	}
	if (check_grammar(token) < -1)
	{
		printf("lexer error -> check_grammar\n"); //나중에 삭제!!!
		return (-1);
	}

	// print_type(token);

	return (0);
}

// 리다이렉션 + filename 세트로 처리하고, 처음 나오는 word를 cmd로
