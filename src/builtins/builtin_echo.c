#include "libft.h"
#include "builtins.h"
#include <stdio.h>

int	builtin_echo(char **argv)
{
	int	i;
	int	nl_flag;

	i = 1;
	nl_flag = 0;
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		nl_flag = 1;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (nl_flag == 0)
		printf("\n");
	return (0);
}
