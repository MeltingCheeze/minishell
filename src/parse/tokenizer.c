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
			q = (line + i);
			if ((i > 1 && (*(q - 1) == BSLASH) && (*(q - 2) != BSLASH))
				|| (i == 1 && (*(q - 1) == BSLASH)))
				q = 0;
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

	is_quote = 0;
	if (*sep == SINGLE || *sep == DOUBLE)
		is_quote = 1;
	content = ft_strndup(line, sep + is_quote - line);
	if (content == NULL)
		ft_error("malloc fail(strdup) : ");
	tokenadd_back(token, tokennew(content, n, *sep));
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
		if (*line && !quote1 && !delim)
		{
			tokenadd_back(token, tokennew(ft_strdup(line), n, SPACE));
			line = 0;
		}
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
		else
		{
			tokenadd_back(token, tokennew(ft_strdup(line), n, SPACE));
			line = 0;
		}
	}
}

t_token	*tokenizer(char *line)
{
	t_token	*token;

	token = 0;
	make_tokens(&token, line);
	tokenprint(&token);
	return (token);
}
