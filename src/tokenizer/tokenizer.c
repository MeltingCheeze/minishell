#include "parser.h"
#include "libft.h"

static int	destroy_token(t_token **token, char *line, int cnt)
{
	tokenclear(token);
	*(line + cnt - 1) = 0;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(line, 2);
	// g_last_exit_value = 258;
	return (258);
}

static int	add_token(t_token **token, char **start, char **cur, size_t len)
{
	int	cnt;

	cnt = 1;
	if (ft_strchr(SEPS, **cur))
		tokenadd_back(token, tokennew(ft_substr(*start, 0, len)));
	else
	{
		while (**cur == *(*cur + cnt))
			cnt++;
		if (cnt > 2 || (cnt > 1 && (**cur == '|')))
		{
			destroy_token(token, *cur, cnt);
			return (1);
		}
		if (len && !ft_strchr(SEPS, **cur))
			tokenadd_back(token, tokennew(ft_substr(*start, 0, len)));
		tokenadd_back(token, tokennew(ft_substr(*cur, 0, cnt)));
	}
	*start += len + cnt;
	while (**start && ft_strchr(SEPS, **start))
		(*start)++;
	*cur = *start - 1;
	return (0);
}

static void	make_token(t_token **token, char *cur)
{
	char	quote;
	char	*start;

	quote = 0;
	while (*cur && ft_strchr(SEPS, *cur))
		cur++;
	start = cur;
	while (*cur)
	{
		if (!quote && (*cur == '"' || *cur == '\''))
			quote = *cur;
		else if (quote && (quote == *cur))
			quote = 0;
		else if (!quote && ft_strchr(DELIMS, *cur))
		{
			if (add_token(token, &start, &cur, cur - start) != 0)
				return ;
		}
		cur++;
	}
	if (cur - start)
		tokenadd_back(token, tokennew(ft_strdup(start)));
}

t_token	*tokenizer(char *line)
{
	t_token	*token;

	token = 0;
	make_token(&token, line);
	return (token);
}
