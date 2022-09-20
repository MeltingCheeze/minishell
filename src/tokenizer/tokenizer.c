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

static int	count_special_char(char *str)
{
	int	cnt;

	if (cnt != '<' && cnt != '>' && cnt != '|')
		return (0);
	cnt = 1;
	while (*str == *(str + cnt))
		cnt++;
	//if (cnt > 2 || (cnt > 1 && (*str == '|')))
	//	//destroy_token(token, str, cnt);
	//	cnt = -1;
	return (cnt);
}

static void	add_tokens(t_token **token, char *start, char *cur, int cnt)
{

	if (start != cur)
		tokenadd_back(token, tokennew(ft_substr(start, 0, cur - start)));
	if (cnt)
		tokenadd_back(token, tokennew(ft_substr(cur, 0, cnt)));
}


static void	check_line(t_token **token, char *line)
{
	char	quote;
	char	*cur;
	int		cnt;

	quote = 0;
	if (*line == 0)
		return ;
	while (*line && ft_strchr(SEPS, *line))
		line++;
	cur = line;
	while (*cur)
	{
		if (!quote && (*cur == '"' || *cur == '\''))
			quote = *cur;
		else if (quote && (quote == *cur))
			quote = 0;
		else if (quote == 0 && ft_strchr(DELIMS, *cur))
		{
			cnt = count_special_char(cur);
			add_tokens(token, line, cur, cnt);
			return (check_line(token, cur + cnt));
		}
		cur++;
	}
	if (cur - line)
		tokenadd_back(token, tokennew(ft_strdup(line)));
}

t_token	*tokenizer(char *line)
{
	t_token	*token;

	token = 0;
	check_line(&token, line);
	return (token);
}
