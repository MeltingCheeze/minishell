#include "minishell.h"

static void	make_token(t_token **token, char *line)
{
	char	has;
	size_t	size;

	has = 0;
	size = -1;
	while (*(line + (++size)))
	{
		if (!has && (*(line + size) == DOUBLE || *(line + size) == SINGLE))
			has = *(line + size);
		else if (has && (has == *(line + size)))
			has = 0;
		else
		{
			if (!has && (*(line + size) == SPACE))
			{
				tokenadd_back(token, tokennew(ft_strndup(line, size)));
				line += size;
				size = -1;
				while (*line == SPACE)
					line++;
			}
		}
	}
	if (size)
		tokenadd_back(token, tokennew(ft_strndup(line, size)));
}

t_token *tokenizer(char *line)
{
	t_token	*token;

	token = 0;
	while (*line == SPACE)
		line++;
	make_token(&token, line);
	tokenprint(&token);
	return (token);
}
