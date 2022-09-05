#include "expansion.h"
#include <stdio.h> // 나중에 지우기

static char	*do_expand(t_env *env, char *content, char *joined)
{
	int		key_len;
	char	*key;
	char	*value;
	char	*result;

	key_len = 0;
	while (is_valid_env_name(*(content + key_len)))
	{
		if (*(content+ key_len) == '\0')
			break ;
		key_len++;
	}
	if (key_len == 0)
		return (NULL);
	key = ft_substr(content, 0, key_len);
	value = find_env_value(env, key);
	result = join_expand(joined, value);
	free(key);
	free(value);
	return (result);
}

static void	tokenizer(t_token *token, char *result)
{
	(void)token;
	(void)result;
	return ;
}

static void	param_expand(t_env *env, t_token *token, char *content)
{
	char	*result;
	char	has;
	int		size;

	has = 0;
	size = -1;
	result = 0;
	while (*(content + (++size)))
	{
		if (!has && (*(content + size) == '"' || *(content + size) == '\''))
			has = *(content + size);
		else if (has && (has == *(content + size)))
			has = 0;
		else if ((has != '\'') && (*(content + size) == '$'))
		{
			content += size;
			size = 0;
			result = do_expand(env, token, content + 1, );
			if (has)
				tokenizer(token, content);
			content += size;
			size = -1;
		}
	}
	if (size)
		;
	if (!result)
		return ;
	free(content);
	token->content = result;
		// tokenadd_back(token, tokennew(ft_strndup(content, size)));
}

void	parameter_expansion(t_sh *sh, t_token *token)
{
	t_token		*cur;

	cur = token;
	while (cur)
	{
		param_expand(sh->env, cur, cur->content);
		cur = cur->next;
	}
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