#include "minishell.h"

int	env_init(t_env **env, char **envp)
{
	int		i;
	int		j;
	char	*key;
	char	**value;
	t_env	*new;

	i = -1;
	*env = 0;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j])
		{
			if (envp[i][j] == '=')
			{
				key = ft_substr(envp[i], 0, j);
				value = ft_split(envp[i] + j + 1, ':');
				break ;
			}
		}
		new = envnew(key, value);
		envadd_back(env, new);
	}
	return (0);
}

int	env_terminate(t_env **env)
{
	t_env	*cur;
	char	**value;
	int	i;

	cur = *env;
	while(cur->next)
	{
		free(cur->key);
		value = cur->value;
		cur = cur->next;
		i = -1;
		while (value[++i])
		{
			free(value[i]);
			value[i] = 0;
		}
		free(value);
	}
	value = 0;
	return (0);
}

t_env	*envnew(char *key, char **value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		ft_error("malloc error(envnew) : ");
	new->key = key;
	new->value = value;
	new->next = 0;
	return (new);
}

void	envadd_back(t_env **env, t_env *new)
{
	t_env	*cur;

	if (env == NULL)
	{
		printf("env == NULL\n");
		return ;
	}
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

char	**find_env_value(t_env **env, char *key)
{
	t_env	*cur;

	if (env == NULL)
	{
		printf("env == NULL\n");
		return (NULL);
	}
	cur = *env;
	while (cur)
	{
		if(ft_strcmp(cur->key, key))
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}
