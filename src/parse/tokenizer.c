#include "minishell.h"

static char	*find_quote(char *line, t_bool find_old)
{
	static char	*has = 0;
	char		*q;
	int			i;

	if (find_old == TRUE)
		return (has);
	q = 0;
	i = -1;
	while (!q && *(line + (++i)))
	{
		if (((!has) && ((*(line + i) == SINGLE) || (*(line + i) == DOUBLE)))
			|| (has && *has && (*(line + i) == *has)))
			q = (line + i);
	}
	if (has)
		has = 0;
	else if (q && !has)
		has = q;
	return (q);
}

static char	*add_token(t_token **token, char *line, char *sep, int n)
{
	char	*content;
	char	*quote1;
	int		is_quote;
	int		need_sep;
	char	c;

	c = *sep;
	is_quote = 0;
	need_sep = 0;
	quote1 = find_quote(line, TRUE);
	if ((c == SINGLE) || (c == DOUBLE))
		is_quote = 1;
	else if (c != SPACE)
	{
		c = SPACE;
		need_sep = 1;
	}
	content = ft_strndup(line + is_quote, sep + need_sep - is_quote - line);
	if (content == NULL)
		ft_error("malloc fail(strdup) : ");
	if (*content == 0)
		free(content);
	else
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
	if (line)
		delim = ft_strchr(line, SPACE);
	while (line && *line && (is_first || *(line - 1) != SPACE))
	{
		if (is_first == 1)
			is_first = 0;
		if (quote1)
			quote2 = find_quote(quote1 + 1, FALSE);
		if ((!quote1 && delim) || (quote1 && (delim && (delim < quote1))))
			line = add_token(token, line, delim, n);
		else if ((quote1 && !delim) || (quote1 && (delim && (delim > quote1))))
			line = add_token(token, line, quote2, n);
		quote1 = find_quote(line, FALSE);
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
		quote = find_quote(line, FALSE);
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

t_token	*tokenizer(char *line, size_t len)
{
	t_token	*token;
	char	*buf;

	token = 0;
	buf = (char *)malloc(sizeof(char) * len + 3);
	if (buf == NULL)
	{
		//ft_putstr_fd(STDERR_FILENO, "malloc error (buf - tokenizer)");
		ft_error("malloc error (buf)");
	}
	buf[0] = SPACE;
	ft_memcpy(buf + 1, line, len);
	buf[len + 1] = SPACE;
	buf[len + 2] = 0;
	while (*buf == ' ')
		buf++;
	make_tokens(&token, buf);
	tokenprint(&token);
	return (token);
}
