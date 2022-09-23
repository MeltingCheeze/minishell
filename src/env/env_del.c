/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:32:37 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/23 13:32:38 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdlib.h>

static void	delete_env(t_env **env)
{
	free((*env)->key);
	free((*env)->value);
	free(*env);
	*env = 0;
}

static void	delete_head(t_env_info *env_info)
{
	t_env	*env;

	env = env_info->head;
	if (env_info->size != 1)
		env_info->head = env_info->head->next;
	else
		env_info->head = 0;
	delete_env(&env);
}

static t_env	*find_prev_env(t_env *env, char *key)
{
	t_env	*prev;

	while (env->next)
	{
		prev = env;
		env = env->next;
		if (!ft_strcmp(env->key, key))
			return (prev);
	}
	return (0);
}

static void	update_prev_env(t_env *prev)
{
	if (prev->next->next)
		prev->next = prev->next->next;
	else
		prev->next = 0;
}

void	env_del(t_env_info *env_info, char *key)
{
	t_env	*env;
	t_env	*prev;

	env = env_info->head;
	if (env == NULL)
		return ;
	if (!ft_strcmp(env->key, key))
	{
		delete_head(env_info);
		env_info->size--;
		return ;
	}
	prev = find_prev_env(env, key);
	if (prev == NULL)
		return ;
	env = prev->next;
	update_prev_env(prev);
	delete_env(&env);
	env_info->size--;
}
