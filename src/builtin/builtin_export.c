/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:36 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 19:19:25 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"
#include "builtin.h"

#define SHELL_NAME "minishell: "

static int	export_err(char *content)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	return (1);
}

static int	check_env_name(char *s)
{
	char	*cur;

	cur = s;
	while (*cur != '=' && is_valid_env_name(*cur))
		cur++;
	if (*cur && *cur != '=')
		return (1);
	return (0);
}

int	builtin_export(char **argv, t_env_info *env_info)
{
	char	**envp;
	int		rvalue;

	rvalue = 0;
	envp = argv;
	if (!*(envp + 1) || !**(envp + 1)) // 수정 필요!!!!!!!!
	{
		no_argv_print(env_info);
		return (rvalue);
	}
	while (*(++envp))
	{
		if (is_valid_env_first_name(**envp) && !check_env_name(*envp)) // 수정 필요!!!!!!!!
			export_new(env_info, *envp);
		else
			rvalue = export_err(*envp);
	}
	ft_free_pptr((void ***)&env_info->envp);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (rvalue);
}
