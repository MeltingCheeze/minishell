/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:52:59 by hyko              #+#    #+#             */
/*   Updated: 2022/09/26 14:31:51 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	update_env(t_env *env, char *envp)
{
	char	*value;

	value = set_env_value(envp);
	if (env->value)
		free(env->value);
	env->value = value;
}

void	export_new(t_env_info *env_info, char *envp)
{
	t_env	*new_env;
	char	*key;

	key = set_env_key(envp);
	new_env = find_env(env_info->head, key);
	free(key);
	if (new_env)
	{
		if (!ft_strcmp(envp, "OLDPWD"))
			return ;
		update_env(new_env, envp);
		return ;
	}
	new_env = env_new(envp);
	env_add_back(&env_info->head, new_env);
	env_info->size++;
}
