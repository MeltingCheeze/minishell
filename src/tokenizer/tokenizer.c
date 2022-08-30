#include "minishell.h"

static void	destroy_token(t_token **token, char *line, size_t cnt)
{
	tokenclear(token);
	*(line + cnt - 1) = 0;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(line, 2);
}

static int	add_token(t_token **token, char *line, size_t *size, char sep)
{
	size_t	cnt;

	cnt = 0;
	if (sep == SPACE)
		tokenadd_back(token, tokennew(ft_strndup(line, *size)));
	else
	{
		while (*(line + *size) == *(line + *size + cnt))
			cnt++;
		if (cnt > 2 || (cnt > 1 && (*(line + *size) == '|')))
		{
			destroy_token(token, line + *size, cnt);
			return (1);
		}
		if (size && !ft_strchr(SEPS, *line))
			tokenadd_back(token, tokennew(ft_strndup(line, *size)));
		tokenadd_back(token, tokennew(ft_strndup(line + *size, cnt)));
		*size += cnt;
	}
	return (0);
}

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
		else if (!has && ft_strchr(SEPS, *(line + size)))
		{
			if (add_token(token, line, &size, *(line + size)) != 0)
				return ;
			line += size;
			size = -1;
			while (*line == SPACE)
				line++;
		}
	}
	if (size)
		tokenadd_back(token, tokennew(ft_strndup(line, size)));
}

t_token	*tokenizer(char *line)
{
	t_token	*token;

	token = 0;
	while (*line == SPACE)
		line++;
	make_token(&token, line);
	if (token)
		tokenprint(&token);
	return (token);
}
