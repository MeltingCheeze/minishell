#include "parse.h"

void	token_init(t_token *token)
{
	token->word = 0;
	token->n = 0;
	token->next = 0;
}

t_token	*tokennew(char *word, int n, char sep)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		ft_error("malloc error(tokennew) : ");
	new->word = word;
	new->n = n;
	new->sep = sep;
	//new->size = ft_strlen(word);
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

void	tokenprint(t_token **token)
{
	t_token	*cur;

	cur= *token;
	while (cur)
	{
		printf("%s\033[0;33m(%c, %d)\033[0m\n", cur->word, cur->sep, cur->n);
		cur= cur->next;
	}
}

void	tokenclear(t_token **token)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *token;
	while (cur)
	{
		tmp = cur;
		cur= cur->next;
		free(tmp->word);
		tmp->word = NULL;
		free(tmp);
		tmp = NULL;
	}
}
