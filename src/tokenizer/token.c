#include "parser.h"

void	token_init(t_token *token)
{
	token->content = 0;
	token->next = 0;
}

t_token	*tokennew(char *content)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	// if (!new)
	// 	ft_error("malloc error(tokennew) : ");
	new->content = content;
	new->type = 0;
	new->next = 0;
	return (new);
}

void	tokenadd_back(t_token **token, t_token *new)
{
	t_token	*cur;

	if (token == 0)
		return ;
	if (*token == 0)
	{
		*token = new;
		return ;
	}
	cur = *token;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	tokenclear(t_token **token)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *token;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->content);
		tmp->content = 0;
		free(tmp);
	}
	*token = 0;
}
