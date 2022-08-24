#include "minishell.h"

static char	*check_quotes(char *line, int *has)
{
	static char *quote = 0;

	if (*has == 0)
		quote = 0;
	if (*line == SINGLE && *has == 0)
	{
		*has += SINGLE;
		quote = line;
	}
	else if (*line == SINGLE && *has == SINGLE)
		*has -= SINGLE;
	else if (*line == SINGLE && *has == DOUBLE)
		;
	else if (*line == DOUBLE && *has == 0)
	{
		*has += DOUBLE;
		quote = line;
	}
	else if (*line == DOUBLE && *has == SINGLE)
		;
	else if (*line == DOUBLE && *has == DOUBLE && *(line - 1) != '\\')
		*has -= DOUBLE;
	return (quote);
}

static char	*alloc_token(const char *s1, size_t n, char **quote)
{
	char	*result;
	size_t	i;
	size_t	cnt;

	result = (char *)malloc(sizeof(char) * (n + 1));
	if (!result)
		ft_error("malloc error(token) : ");
	i = -1;
	cnt = -1;
	while (++i < n)
	{
		if ((*quote == 0) && (s1[i] != BSLASH
				|| (s1[i] == BSLASH && s1[i + 1] == BSLASH)))
			result[++cnt] = s1[i];
		if (*quote)
		{
			//if ((**quote == SINGLE) && (s1[i] != **quote))
			//	result[++cnt] = s1[i];
			//else if ((**quote == DOUBLE) && (s1[i] != **quote))
			//	result[++cnt] = s1[i];
			if ((**quote == DOUBLE) && ((s1[i] == BSLASH) && s1[i + 1] == DOUBLE))
					result[++cnt] = s1[i + 1];
		}
	}
	while (cnt < n)
		result[cnt++] = '\0';
	return (result);
}

static void	make_token(t_token **token,
	const char *line, char *delim, char *quote)
{
	if (*token == 0)

	token = alloc_token(line, delim - line, *quote);
	token_add_back(&delim, line);
}

void	script_to_tokens(t_token *token, char *line)
{
	char	*delim;
	char	*quote;
	int		has;
	int		i;

	while (*line && (*line == ' '))
		line++;
	has = 0;
	while (*line)
	{
		delim = 0;
		quote = 0;
		while (!delim && !quote)
		{
			delim = ft_strchr(line, ' ');
			i = -1;
			while (++i < delim - line)
				quote = check_quotes(line + i, &has);
			if (quote && has)
				delim = ft_strchr(quote + 1, *quote);
		}
		make_token(&token, line, delim, quote);
		while (*line && (*line == ' '))
			line++;
	}
}
