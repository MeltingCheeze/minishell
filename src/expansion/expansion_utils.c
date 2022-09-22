#include "expansion.h"
#include "libft.h"

char	*attach_str(char *joined, char *expand)
{
	char	*result;

	result = ft_strjoin(joined, expand);
	free(joined);
	return (result);
}

char	*attach_param_prestr(char *joined, char *start, char *cur)
{
	char	*prestr;
	char	*result;

	if (joined == 0 && (start != cur))
	{
		result = ft_substr(start, 0, cur - start);
		return (result);
	}
	prestr = ft_substr(start, 0, cur - start);
	result = attach_str(joined, prestr);
	free(prestr);
	return (result);
}

char	*attach_param_str(t_env *env, char *joined, char *cur)
{
	char	*key;
	char	*value;
	char	*result;

	key = set_env_key(cur + 1);
	value = find_env_value(env, key);
	result = joined;
	if (*key && value)
		result = attach_str(joined, value);
	free(key);
	return (result);
}

int	count_key_len(char *str)
{
	int	len;

	if (*str == '?')
		return (1);
	len = 0;
	while (is_valid_env_name(*(str + len)))
		len++;
	return (len);
}
