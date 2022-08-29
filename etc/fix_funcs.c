#include "minishell.h"

static int	add_token()
{	
}

static void	make_token(t_token **token, char *line, size_t size, char sep)
{
	int	cnt;

	cnt = 0;
	if (sep == SPACE)
		tokenadd_back(token, tokennew(ft_strndup(line, size)));
	else
	{
		while (line)
		{
			cnt++;
		}
	}
	
}

t_token *tokenizer(char *line)
{
	t_token	*token;
	char	has;
	size_t	size;

	token = 0;
	while (*line == SPACE)
		line++;
	has = 0;
	size = -1;
	while (*(line + (++size)))
	{
		if (!has && (*(line + size) == DOUBLE || *(line + size) == SINGLE))
			has = *(line + size);
		else if (has && (has == *(line + size)))
			has = 0;
		else if (!has && ft_strchr(SEPS, *(line + size)))
		{
			make_token(&token, line, size, *(line + size));
			line += size;
			size = -1;
			while (*line == SPACE)
				line++;
		}
	}
	if (size)
		tokenadd_back(token, tokennew(ft_strndup(line, size)));
	tokenprint(&token);
	return (token);
}
