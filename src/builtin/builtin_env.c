/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:30 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:42:31 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include <stdio.h>

#define SHELL_NAME "minishell: "

static int	env_err(void)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("env: wrong number of arguments\n", 2);
	ft_putstr_fd("usage: env\n", 2);
	return (1);
}

static void	envp_print(char	**envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

int	builtin_env(char **argv, t_env_info *env_info)
{
	++argv;
	if (*argv && **argv)
		return (env_err());
	envp_print(env_info->envp);
	return (0);
}
