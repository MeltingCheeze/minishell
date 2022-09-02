#include "expansion.h"

int	is_valid_env_name(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || (c == '_'));
}

char	*expand_content(t_env *env, int start, int len, char *content)
{
	char	*key;
	char	*value;
	char	result;

	key = ft_substr(content, 0, len - 1);
	value = find_env_value(env, key);
	free(key);
	return(value);
}


// static void	add_expand(t_env *env, char *start)
// {
// 	int	size;

// 	size = 1;
// 	while (ft_strchr(" '\"", *(start + size)))
// 	{
// 		if (*(start + size) == '\0')
// 			break ;
// 		size++;
// 	}
// 	expand_content(sh->env, start, size - 1, start);
// 	// expandnew( , start - token->content , size - 1);
// 	start = ft_strchr(start + size, '$');
// }

int	parameter_expansion(t_sh *sh, t_token *token)
{
	t_expand	*expand;
	char		*start;
	int			start_idx;
	int			size;
	char		*content;

	expand = 0;
	start = ft_strchr(token->content, '$');
	while (start && is_valid_env_name(*(start + 1)))
	{
		size = 1;
		while (ft_strchr(" '\"", *(start + size)))
		{
			if (*(start + size) == '\0')
				break ;
			size++;
		}
		content = expand_content(sh->env, start, size - 1, start);
		start_idx = start - token->content;
		expandadd_back(&expand, expandnew(content, start_idx, size - 1));
		start = ft_strchr(start + size, '$');
	}
	(loc_end - loc_start + len)
}