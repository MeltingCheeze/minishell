#include "minishell.h"
#include "executor.h"
#include "builtin.h"

int execve_builtin(char **argv, t_sh *sh, t_script *cur_cmd, t_builtin builtin)
{
	int	rvalue;

	rvalue = 0;
	if (builtin == EXPORT)
		rvalue = builtin_export(argv, &sh->env_info);
	else if (builtin == ENV)
		rvalue = builtin_env(argv, &sh->env_info);
	else if (builtin == UNSET)
		rvalue = builtin_unset(argv, &sh->env_info);
	else if (builtin == ECHO)
		rvalue = builtin_echo(argv, cur_cmd);
	else if (builtin == PWD)
		rvalue = builtin_pwd(cur_cmd);
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
		result = ECHO;
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
