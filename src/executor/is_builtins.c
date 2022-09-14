#include "libft.h"

int	is_builtins(char *cmd)
{
	int	result;

	result = 0;
	if (!ft_strcmp(cmd, "echo"))
		result = 1;
	else if (!ft_strcmp(cmd, "cd"))
		result = 1;
	else if (!ft_strcmp(cmd, "pwd"))
		result = 1;
	else if (!ft_strcmp(cmd, "export"))
		result = 1;
	else if (!ft_strcmp(cmd, "unset"))
		result = 1;
	else if (!ft_strcmp(cmd, "env"))
		result = 1;
	else if (!ft_strcmp(cmd, "exit"))
		result = 1;
	return (result);
}