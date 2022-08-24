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

static char	*make_token(t_token **token, char *line, char *sep, int is_quote)
{
	char	*content;

	content = ft_strndup(line, sep + is_quote - line);
	tokenadd_back(token, tokennew(content));
	line = sep + 1;
	while (*line == SPACE)
		line++;
	return (line);
}

static void	make_tokens(t_token **token, char *line)
{
	char	*content;
	char	*quote;
	char	*tmp;
	char	*delim;

	(void)tmp;
	tmp = find_quote(line);
	while (line && *line)
	{
		quote = tmp;
		delim = ft_strchr(line, SPACE);
		if (quote)
		{
			while (delim && (delim < quote))
			{
				line = make_token(token, line, delim, 0);
				delim = ft_strchr(delim + 1, SPACE);
				printf("quote : %s delim %s\n", quote, delim);
			}
			quote = find_quote(quote + 1);
			tmp = find_quote(quote + 1);
			delim = ft_strchr(quote, SPACE);
			if (tmp && (delim > quote))
			{
				quote = find_quote(quote + 1);
				if (quote && (delim > quote))
					line = make_token(token, line, delim, 0);
				else
					line = make_token(token, line, quote, 1);
				printf("=======d|%s|=======\n", delim);
			}
			else
			{
				line = make_token(token, line, quote, 1);
				printf("=======q|%s|=======\n", quote);
			}
		}
		else
		{
			while (delim)
			{
				//content = ft_strndup(line, delim - line);
				//tokenadd_back(token, tokennew(content));
				//line = delim + 1;
				line = make_token(token, line, delim, 0);
				delim = ft_strchr(delim + 1, SPACE);
			}
			content = ft_strdup(line);
			tokenadd_back(token, tokennew(content));
			line = 0;
		}
	}

}

t_token	*tokenizer(char *line, size_t len)
{
	t_token_lst	*token;
	t_token		*t;
	char		*buf;

	token = 0;
	buf = (char *)malloc(sizeof(char) * (len + 2));
	ft_strcpy(buf, line);
	buf[len] = SPACE;
	buf[len] = 0;
	make_tokens(&token, buf);
	t = token;
	while (t)
	{
		printf("%s\n", t->word);
		t = t->next;
	}
	return (token);
}
