#include "parse.h"


typedef struct s_token
{
	char			*word;
	char			deli;
	int				loc_start;
	int				loc_end;
	struct s_token	*next;
}				t_token;

void	token_lst_init(t_token_lst *token)
{
	token->token = 0;
	token->size = 0;
	token->next = 0;
}

void	tokenlst_add_back(t_token_lst **token_lst, t_token *token)
{
	t_token_lst	*cur_lst;
	t_token_lst *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		ft_error("malloc error(tokelst) : ");
	new->token = token;
	//new->size = ft_strlen(word);
	new->next = 0;
	if (token_lst == 0)
		return ;
	if (*token_lst == 0)
	{
		*token_lst = new;
		return ;
	}
	cur_lst = *token_lst;
	while (cur_lst->next)
		cur_lst = cur_lst->next;
	cur_lst->next = new;
}

t_token	*tokennew(char *word)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		ft_error("malloc error(tokennew) : ");
	new->word = word;
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
