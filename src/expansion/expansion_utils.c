#include "expansion.h"
#include "libft.h"

char	*attach_str(char *joined, char *expand)
{
	char	*result;

	result = ft_strjoin(joined, expand);
	free(joined);
	return (result);
}

char	*do_expand(t_env *env, char *joined, char **start, char **cur)
{
	char	*not_expand;
	char	*key;
	char	*value;

	if (!joined && (*start != *cur))
		joined = ft_substr(*start, 0, *cur - *start);
	else
	{
		not_expand = ft_substr(*start, 0, *cur - *start);
		joined = attach_str(joined, not_expand);
		free(not_expand);
	}
	key = set_env_key(*cur + 1);
	value = find_env_value(env, key);
	if (*key && value)
		joined = attach_str(joined, value);
	*start = *cur + ft_strlen(key) + 1;
	*cur = *start - 1;
	free(key);
	return (joined);
}
