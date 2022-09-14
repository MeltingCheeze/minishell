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
		new = envnew(envp[i]);
		if (new)
			envadd_back(&env_info->head, new);
		i++;
	}
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

t_env	*envnew(char *s)
{
	t_env	*new;
	char	*key;
	char	*value;
	char	*delim;

	delim = ft_strchr(s, '=');
	if (delim == 0)
		return (NULL);
	key = ft_substr(s, 0, delim - s);
	while (ft_strchr(" \n\t", *(delim + 1)))
		delim++;
	value = ft_strdup(delim + 1);
	new = (t_env *)malloc(sizeof(t_env));
	// if (!new)
	// 	ft_error("malloc error(envnew) : ");
	new->key = key;
	new->value = value;
	new->next = 0;
	return (new);
}

void	envadd_back(t_env **env, t_env *new)
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

