/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:19:41 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 19:21:17 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtin.h"

int	execve_builtin(char **argv, t_sh *sh, t_builtin builtin)
{
	int	rvalue;

	rvalue = 0;
	// 수정 필요!!!!!!!! (ex. argv = {"echo", "\0", "a", "b", NULL} )
	if (builtin == EXPORT)
		rvalue = builtin_export(argv, &sh->env_info);
	else if (builtin == ENV)
		rvalue = builtin_env(argv, &sh->env_info);
	else if (builtin == UNSET)
		rvalue = builtin_unset(argv, &sh->env_info);
	else if (builtin == B_ECHO)
		rvalue = builtin_echo(argv);
	else if (builtin == PWD)
		rvalue = builtin_pwd();
	else if (builtin == CD)
		rvalue = builtin_cd(argv, &sh->env_info);
	else if (builtin == EXIT)
		rvalue = builtin_exit(argv, sh);
	return (rvalue);
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
