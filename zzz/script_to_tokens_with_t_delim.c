#include "minishell.h"


typedef struct s_quotes
{
	char *start;
	char *end;
	char c;
}				t_quotes;

typedef struct s_token_delim
{
	char	*space;
	char	*rslash;
	t_quotes sq;
	t_quotes dq;
	int		cnt;
}			t_token_delim;

static void quotes_init(t_token_delim *delim, const char *str)
{
	delim->space = ft_strchr(str, ' ');
	delim->rslash = ft_strchr(str, '\\');
	delim->sq.start = ft_strchr(str, '\'');
	delim->sq.end = ft_strchr(delim->sq.start + 1, '\'');
	delim->sq.c = '\'';
	delim->dq.start = ft_strchr(str, '"');
	delim->dq.end = ft_strchr(delim->dq.start + 1, '"');
	delim->dq.c = '"';
	delim->cnt = !!(delim->space) + !!(delim->sq.start) + !!(delim->dq.start);
}

static void find_quotes(t_quotes *quotes, const char *str)
{
	quotes->start = ft_strchr(str, quotes->c);
	quotes->end = ft_strchr(quotes->start + 1, quotes->c);
}

static int set_quotes(t_token_delim *delim, t_quotes *sq, t_quotes *dq)
{
	t_quotes	*first;
	t_quotes	*next;

	if (sq->start == 0 || dq->start == 0)
		return (0);
	first = dq;
	next = sq;
	if (sq->start < dq->start)
	{
		first = sq;
		next = dq;
	}
	if (delim->rslash == first->start - 1)
	{
		//*(delim->rslash) = ' ';
		delim->rslash = ft_strchr(delim->rslash + 1, '\\');
		find_quotes(first->start, first->end);
	}
	else
	{
		while (next->start && (next->start < first->end))
			find_quotes(next->start, next->end);
		return (0);
	}
	return (1);
}

static void	set_token_delim(t_token_delim *delim, char *line)
{
	while (set_quotes(delim, &delim->sq, &delim->dq))
		;
	while ((delim->space > delim->sq.start &&  delim->space < delim->sq.end)
			|| (delim->space > delim->dq.start &&  delim->space < delim->dq.end))
	{
		delim->space = ft_strchr(delim->space + 1, ' ');
	}
	delim->cnt = !!(delim->space) + !!(delim->sq.start) + !!(delim->dq.start);
}

int	script_to_tokens(char *line)
{
	t_token			token;
	t_token_delim	delim;

	while (*line && (*line == ' '))
		line++;
	delim_init(delim, line);
	while (delim.cnt)
	{
		set_token_delim(&delim, line);
		token_add_back(&delim, line);
		line
		while (*line && (*line == ' '))
			line++;
	}
	return ()
}


//	t_quotes	quotes[2];
//	quotes_init(line, quotes);
static void new_quotes_init(const char *str, t_quotes *quotes)
{
	t_quotes *first;
	t_quotes *second;

	quotes[0].start = ft_strchr(str, SINGLE);
	if (quotes[0].start == 0)
		quotes[0].end = 0;
	else
		quotes[0].end = ft_strchr(quotes[0].start + 1, SINGLE);
	quotes[1].start = ft_strchr(str, DOUBLE);
	if (quotes[1].start == 0)
		quotes[1].end = 0;
	else
		quotes[1].end = ft_strchr(quotes[1].start + 1, DOUBLE);
	first = quotes[0];
	second = quotes[1];
	if (sq->start < dq->start)
	{
		first = sq;
		second = dq;
	}
	while (second->start && (second->start < first->end))
	{

	}
}
