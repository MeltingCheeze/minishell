/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:19:41 by hyko              #+#    #+#             */
/*   Updated: 2022/09/26 15:03:32 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtin.h"

int	execve_builtin(char **argv, t_sh *sh, t_builtin builtin)
{
	int	result;

	result = 0;
	if (builtin == EXPORT)
		result = builtin_export(argv, &sh->env_info);
	else if (builtin == ENV)
		result = builtin_env(argv, &sh->env_info);
	else if (builtin == UNSET)
		result = builtin_unset(argv, &sh->env_info);
	else if (builtin == B_ECHO)
		result = builtin_echo(argv);
	else if (builtin == PWD)
		result = builtin_pwd(sh);
	else if (builtin == CD)
		result = builtin_cd(argv, &sh->env_info);
	else if (builtin == EXIT)
		result = builtin_exit(argv, sh);
	return (result);
}

t_builtin	is_builtin(t_token *token)
{
	t_builtin	result;

	result = NONE;
	while (token && (token->type != CMD))
		token = token->next;
	if (!token)
		return (result);
	if (!ft_strcmp(token->content, "echo"))
		result = B_ECHO;
	else if (!ft_strcmp(token->content, "cd"))
		result = CD;
	else if (!ft_strcmp(token->content, "pwd"))
		result = PWD;
	else if (!ft_strcmp(token->content, "export"))
		result = EXPORT;
	else if (!ft_strcmp(token->content, "unset"))
		result = UNSET;
	else if (!ft_strcmp(token->content, "env"))
		result = ENV;
	else if (!ft_strcmp(token->content, "exit"))
		result = EXIT;
	return (result);
}
