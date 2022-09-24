/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:52:59 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 14:52:00 by chaejkim         ###   ########.fr       */
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

t_env	*init_pwd_env(char *envp)
{
	t_env	*pwd_env;
	char	*value;
	char	*tmp;

	value = getcwd(NULL, 0);
	tmp = ft_strjoin(envp, "=");
	envp = ft_strjoin(tmp, value);
	pwd_env = env_new(envp);
	free(value);
	free(tmp);
	free(envp);
	return (pwd_env);
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
	if (!ft_strcmp(envp, "PWD"))
		new_env = init_pwd_env(envp);
	else
		new_env = env_new(envp);
	env_add_back(&env_info->head, new_env);
	env_info->size++;
}
