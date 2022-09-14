#include "builtins.h"
#include "libft.h"

t_builtin	is_builtins(t_token *token)
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