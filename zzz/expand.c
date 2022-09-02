#include "expansion.h"

t_expand	*expandnew(char *expand, int loc_start, int loc_end, int len)
{
	t_expand	*new;

	new = (t_expand *)malloc(sizeof(t_expand));
	// if (!new)
	// 	ft_error("malloc error(expandnew) : ");
	new->expand = expand;
	new->loc_start = loc_start;
	new->loc_end = loc_end;
	new->len = ft_strlen(expand);
	new->next = 0;
	return (new);
}

void	expandadd_back(t_expand **expand, t_expand *new)
{
	t_expand	*cur;

	if (expand == 0)
		return ;
	if (*expand == 0)
	{
		*expand = new;
		return ;
	}
	cur = *expand;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	expandclear(t_expand **expand)
{
	t_expand	*cur;
	t_expand	*tmp;

	cur = *expand;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp->expand);
		tmp->expand = 0;
		free(tmp);
	}
	*expand = 0;
}