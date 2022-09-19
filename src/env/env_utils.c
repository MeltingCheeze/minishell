#include "env.h"
#include "libft.h"
#include <stdlib.h>

char	**make_envp(t_env *env, int env_size)
{
	char	**result;
	size_t	len;
	int		i;

	write(1, "=======make_envp======\n", 24); // test
	result = (char **)malloc(sizeof(char *) * (env_size + 1));
	i = 0;
	while (env)
	{
		if (env->value)
		{
			len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
			result[i] = (char *)malloc(sizeof(char) * len);
			ft_strcpy(result[i], env->key);
			result[i][ft_strlen(env->key)] = '=';
			result[i][ft_strlen(env->key) + 1] = '\0';
			ft_strlcat(result[i], env->value, len);
			i++;
		}
		env = env->next;
	}
	result[i] = 0;
	return (result);
}

t_env	*find_env(t_env *env, char *key)
{
	if (env == NULL)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*find_env_value(t_env *env, char *key) // 나중에 지우기
{
	if (env == NULL)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*getkey(char *s)
{
	char	*result;
	int		len;

	len = 0;
	while (is_valid_env_name(*(s + len)) && (*(s + len) != '\0'))
		len++;
	result = ft_substr(s, 0, len);
	return (result);
}

char	*getvalue(char *s)
{
	char	*result;
	char	*delim;

	delim = ft_strchr(s, '=');
	if (delim)
		result = ft_strdup(delim + 1);
	else
		result = NULL;
	return (result);
}

int	is_valid_env_first_name(char c)
{
	return (ft_isalpha(c) || (c == '_'));
}

int	is_valid_env_name(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || (c == '_'));
}
