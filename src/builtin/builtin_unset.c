/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:43 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 14:32:30 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"
#include "builtin.h"

#define SHELL_NAME "minishell: "

static int	unset_err(char *content)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	return (1);
}

static int	check_env_name(char *s)
{
	char	*cur;

	cur = s;
	while (is_valid_env_name(*cur))
		cur++;
	if (*cur)
		return (1);
	return (0);
}

static void	unset_env(t_env_info *env_info, char **envp)
{
	char	*key;

	key = set_env_key(*envp);
	env_del(env_info, key);
	free(key);
}

int	builtin_unset(char **argv, t_env_info *env_info)
{
	char	**envp;
	int		result;

	result = 0;
	envp = argv;
	if (!*(envp + 1))
		return (result);
	while (*(++envp))
	{
		if (!**envp
			|| (is_valid_env_first_name(**envp) && !check_env_name(*envp)))
			unset_env(env_info, envp);
		else
			result = unset_err(*envp);
	}
	ft_free_pptr((void ***)&env_info->envp);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (result);
}
