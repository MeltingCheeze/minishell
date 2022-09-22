#include "env.h"
#include "libft.h"
#include <stdlib.h>

int	env_init(t_env_info *env_info, char **envp)
{
	t_env	*new;
	size_t	i;

	i = 0;
	env_info->head = 0;
	while (envp[i])
	{
		new = env_new(envp[i]);
		if (new)
			env_add_back(&env_info->head, new);
		i++;
	}
	export_new(env_info, "OLDPWD");
	env_info->size = i;
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (0);
}

int	env_terminate(t_env **env)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		free(cur->key);
		free(cur->value);
		cur->key = 0;
		cur->value = 0;
		cur = cur->next;
	}
	*env = 0;
	return (0);
}

t_env	*env_new(char *s)
{
	t_env	*new;
	char	*key;
	char	*value;

	key = set_env_key(s);
	value = set_env_value(s);
	new = (t_env *)malloc(sizeof(t_env));
	// if (!new)
	// 	ft_error("malloc error(env_new) : ");
	new->key = key;
	new->value = value;
	new->next = 0;
	return (new);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*cur;

	if (env == NULL)
		return ;
	if (*env == NULL)
	{
		*env = new;
		return ;
	}
	cur = *env;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	env_del(t_env *env, char *key)
{
	t_env	*prev;
	int		need_del;

	need_del = 0;
	if (env == NULL)
		return ;
	while (env->next)
	{
		prev = env;
		env = env->next;
		if (!ft_strcmp(env->key, key))
		{
			need_del = 1;
			break ;
		}
	}
	if (need_del)
	{
		if (prev->next->next)
			prev->next = prev->next->next;
		else
			prev->next = 0;
		free(env->key);
		free(env->value);
		free(env);
	}
	else if (env->next && !ft_strcmp(env->next->key, key))
	{
		prev->next = 0;
		free(env->next->key);
		free(env->next->value);
		free(env->next);
	}
}
