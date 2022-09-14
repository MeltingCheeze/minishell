#include "env.h"
#include "libft.h"

char	*find_env_value(t_env *env, char *key)
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
