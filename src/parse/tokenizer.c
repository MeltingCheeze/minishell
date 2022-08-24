#include "minishell.h"

static char	*find_quote(char *line)
{
	static char	has = 0;
	char		*q;
	int			i;

	q = 0;
	i = -1;
	while (!q && *(line + (++i)))
	{
		if ((!has && ((*(line + i) == SINGLE) || (*(line + i) == DOUBLE)))
			|| (has && (*(line + i) == has)))
		{
			if (check_quote(line, i))
				q = (line + i);
		}
	}
	if (has)
		has = 0;
	else if (q && !has)
		has = *q;
	return (q);
}

static char	*add_token(t_token **token, char *line, char *sep, int n)
{
	char	*content;
	int		is_quote;
	int		c_quote;
	char	c;

	is_quote = 0;
	c_quote = 0;
	c = check_quote(line, sep - line);
	if (c == SINGLE || c == DOUBLE)
		is_quote = 1;
	else
	{
		c = SPACE;
		if (*sep == SINGLE || *sep == DOUBLE)
			c_quote = 1;
	}
	content = ft_strndup(line + is_quote, sep + c_quote - is_quote - line);
	if (content == NULL)
		ft_error("malloc fail(strdup) : ");
	tokenadd_back(token, tokennew(content, n, c));
	line = sep + 1;
	while (*line == SPACE)
		line++;
	return (line);
}

static char	*extend_token(t_token **token, char *line, char *quote1, int n)
{
	char	*quote2;
	char	*delim;
	int		is_first;

	is_first = 1;
	if ((quote1 - 1) && (*(quote1 - 1) != SPACE))
		line = add_token(token, line, quote1 - 1, n);
	delim = ft_strchr(line, SPACE);
	while (line && *line && (is_first || *(line - 1) != SPACE))
	{
		if (is_first == 1)
			is_first = 0;
		if (quote1)
			quote2 = find_quote(quote1 + 1);
		if ((!quote1 && delim) || (quote1 && (delim && (delim < quote1))))
			line = add_token(token, line, delim, n);
		else if ((quote1 && !delim) || (quote1 && (delim && (delim > quote1))))
			line = add_token(token, line, quote2, n);
		quote1 = find_quote(line);
		delim = ft_strchr(line, SPACE);
		if (!quote1 && !delim)
			break ;
	}
	return (line);
}

static void	make_tokens(t_token **token, char *line)
{
	char	*quote;
	char	*delim;
	int		n;

	n = 0;
	while (line && *line)
	{
		quote = find_quote(line);
		delim = ft_strchr(line, SPACE);
		while ((quote && (delim && (delim < quote)))
			|| (!quote && delim))
		{
			line = add_token(token, line, delim, n++);
			delim = ft_strchr(line, SPACE);
		}
		if (quote)
			line = extend_token(token, line, quote, n++);
		if (!quote && !delim)
			break ;
	}
	if (line && *line)
		tokenadd_back(token, tokennew(ft_strdup(line), n, SPACE));
}

t_token	*tokenizer(char *line)
{
	t_token	*token;

	token = 0;
	make_tokens(&token, line);
	tokenprint(&token);
	return (token);
}
