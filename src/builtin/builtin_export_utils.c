/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:34:26 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/23 13:35:04 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

static void	bubble_sort(char **envp, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (envp[j + 1])
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static char	**make_export_arr(t_env *env, int env_size)
{
	char	**result;
	size_t	len;
	int		i;

	result = (char **)malloc(sizeof(char *) * (env_size + 1));
	i = 0;
	while (i < env_size)
	{
		if (env->value)
			len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
		else
			len = ft_strlen(env->key) + 2;
		result[i] = (char *)malloc(sizeof(char) * len);
		ft_strcpy(result[i], env->key);
		if (env->value)
		{
			result[i][ft_strlen(env->key)] = '=';
			result[i][ft_strlen(env->key) + 1] = '\0';
			ft_strlcat(result[i], env->value, len);
		}
		i++;
		env = env->next;
	}
	result[i] = 0;
	return (result);
}

static void	print_export_value(char *value)
{
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(value, STDOUT_FILENO);
	ft_putchar_fd('"', STDOUT_FILENO);
}

void	no_argv_print(t_env_info *env_info)
{
	char	**export_arr;
	char	*key;
	char	*value;
	size_t	i;

	if (env_info->size == 0)
		return ;
	export_arr = make_export_arr(env_info->head, env_info->size);
	bubble_sort(export_arr, env_info->size);
	i = 0;
	while (*export_arr && i < env_info->size)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		key = set_env_key(*(export_arr + i));
		ft_putstr_fd(key, STDOUT_FILENO);
		value = find_env_value(env_info->head, key);
		if (value)
			print_export_value(value);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(key);
		i++;
	}
	ft_free_pptr((void ***)&export_arr);
}
