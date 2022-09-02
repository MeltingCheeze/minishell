#include "expansion.h"
#include <stdio.h> // 나중에 지우기

static int	is_valid_env_name(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || (c == '_'));
}

static char	*find_expand(t_env *env, int len, char *content)
{
	char	*key;
	char	*value;

	key = ft_substr(content, 0, len);
	value = find_env_value(env, key);
	free(key);
	return (value);
}

static char	*join_expand(char *joined, char *expand)
{
	char	*result;

	result = ft_strjoin(joined, expand);
	free(joined);
	return (result);
}

void	parameter_expansion(t_sh *sh, t_token *token)
{
	char		*last;
	char		*cur;
	size_t		size;
	char		*expand;
	char		*result;

	cur = ft_strchr(token->content, '$');
	if (cur && is_valid_env_name(*(cur + 1)))
		result = ft_substr(token->content, 0, cur - token->content);
	else
		result = token->content;
	last = 0;
	while (cur && is_valid_env_name(*(cur + 1)))
	{
		size = 1;
		while (is_valid_env_name(*(cur + size)))
		{
			if (*(cur + size) == '\0')
				break ;
			size++;
		}
		expand = find_expand(sh->env, size - 1, cur + 1);
		result = join_expand(result, expand);
		last = cur;
		cur = ft_strchr(cur + size, '$');
	}
	if (last && (*(last + size) != '\0'))
	{
		last = ft_strjoin(result, last + size);
		free(result);
		result = last;
	}
	token->content = result;
}