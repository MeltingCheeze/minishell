#include "tokenizer.h"
#include "libft.h"
#include <stdio.h>

static int	syntax_err(char *s, int cnt)
{
	*(s + cnt - 1) = 0;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(s, 2);
	g_last_exit_value = 258;
	return (258);
}

static int	count_special_char(char *str)
{
	int	cnt;

	if (*str != '<' && *str != '>' && *str != '|')
		return (0);
	cnt = 1;
	while (*str == *(str + cnt))
		cnt++;
	if (cnt > 2 || (cnt > 1 && (*str == '|')))
	{
		syntax_err(str, cnt);
		return (-1);
	}
	return (cnt);
}

static void	add_tokens(t_token **token, char *start, char *cur, int cnt)
{
	if (start != cur)
		tokenadd_back(token, tokennew(ft_substr(start, 0, cur - start)));
	if (cnt)
		tokenadd_back(token, tokennew(ft_substr(cur, 0, cnt)));
}

static int	check_line(t_token **token, char *line)
{
	char	quote;
	char	*cur;
	int		cnt;

	quote = 0;
	cnt = 0;
	if (*line == 0)
		return (0);
	while (*line && ft_strchr(SEPS, *line))
		line++;
	cur = line;
	while (1)
	{
		if (!quote && (*cur == '"' || *cur == '\''))
			quote = *cur;
		else if (quote && (quote == *cur))
			quote = 0;
		else if (quote == 0 && ft_strchr(DELIMS, *cur))
		{
			cnt = count_special_char(cur);
			if (cnt < 0)
				return (-1);
			add_tokens(token, line, cur, cnt);
			return (check_line(token, cur + cnt));
		}
		cur++;
	}
}

int	tokenizer(t_token **token,char *line)
{
	int		rvalue;

	*token = 0;
	rvalue = check_line(token, line);
	return (rvalue);
}
