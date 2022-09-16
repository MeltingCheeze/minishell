#include "builtins.h"
#include "libft.h"
#include <stdio.h>

int	builtin_cd(char **argv)
{
	char	*path;

	path = argv[1];
	if (chdir(path) < 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (-1);
	}
	return (0);
}
