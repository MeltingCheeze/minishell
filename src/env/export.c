/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:52:59 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:53:42 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

void	export_new(t_env_info *env_info, char *envp)
{
	t_env	*new_env;
	char	*key;
	char	*value;

	key = set_env_key(envp);
	new_env = find_env(env_info->head, key);
	if (new_env)
	{
		value = set_env_value(envp);
		if (new_env->value)
			free(new_env->value);
		new_env->value = value;
		free(key);
		return ;
	}
	new_env = env_new(envp);
	env_add_back(&env_info->head, new_env);
	env_info->size++;
	free(key);
}
