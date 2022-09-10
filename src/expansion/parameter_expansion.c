#include "expansion.h"
#include <stdio.h> // 나중에 지우기

static char	*find_expand(t_env *env, int len, char *content)
{
	char	*key;
	char	*value;

	key = ft_substr(content, 0, len);
	value = find_env_value(env, key);
	free(key);
	return (value);
}

char	*attach_str(char *joined, char *expand)
{
	char	*result;

	result = ft_strjoin(joined, expand);
	free(joined);
	return (result);
}

char	*do_expand(t_env *env, char *joined, char **start, char **cur)
{
	int		len;
	char	*value;

	if (!joined && (*start != *cur))
		joined = ft_substr(*start, 0, *cur - *start);
	else
	{
		value = ft_substr(*start, 0, *cur - *start);
		joined = attach_str(joined, value);
		free(value);
	}
	len = keylen(*cur + 1);
	if (len)
	{
		value = find_expand(env, len, *cur + 1);
		if (value)
			joined = attach_str(joined, value);
	}
	*start = *cur + len + 1;
	*cur = *start - 1;
	return (joined);
}

void	parameter_expansion(t_sh *sh, t_token *token)
{
	char	*start;
	char	*cur;
	char	*result;
	char	has;

	has = 0;
	result = 0;
	cur = token->content;
	start = cur;
	while (*cur)
	{
		if (!has && (*cur == '"' || *cur == '\''))
			has = *cur;
		else if (has == *cur)
			has = 0;
		else if (has != '\'' && *cur == '$' && is_valid_env_name(*(cur + 1)))
			result = do_expand(sh->env, result, &start, &cur);
		cur++;
	}
	if (start)
		result = attach_str(result, start);
	if (!result)
		return ;
	free(token->content);
	token->content = result;
}
