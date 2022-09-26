/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:32:56 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/26 14:18:07 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

int	env_init(t_env_info *env_info, char **envp)
{
	t_env	*new;
	size_t	i;

	i = 0;
	env_info->head = 0;
	env_info->size = 0;
	while (envp[i])
	{
		new = env_new(envp[i]);
		if (new)
		{
			if (!ft_strcmp(new->key, "OLDPWD"))
			{
				if (new->value)
					free(new->value);
				new->value = NULL;
			}
			env_add_back(&env_info->head, new);
		}
		i++;
	}
	env_info->size += i;
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
