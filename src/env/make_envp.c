#include "env.h"
#include "libft.h"
#include <stdlib.h>

char	**make_envp(t_env *env, int env_size)
{
	char	**result;
	size_t	len;
	int		i;

	result = (char **)malloc(sizeof(char *) * (env_size + 1));
	i = 0;
	while (env)
	{
		len = ft_strlen(env->key) + ft_strlen(env->value) + 2; // env에 key_len, val_len 둘까?
		result[i] = (char *)malloc(sizeof(char) * len);
		ft_strcpy(result[i], env->key);
		result[i][ft_strlen(env->key)] = '=';
		result[i][ft_strlen(env->key) + 1] = '\0';
		ft_strlcat(result[i], env->value, len);
		env = env->next;
		i++;
	}
	result[i] = 0;
	return (result);
}
