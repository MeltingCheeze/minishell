#include "builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static int	ft_atoll(const char *str)
{
	int	i;
	int	sign;
	int	length;
	long long	result;

	i = 0;
	sign = 1;
	length = 0;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
		if (str[i] == '\0')
			return (-1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - 48);
		i++;
		length++;
		if (length > 19)
			return (-1);
	}
	return (result * sign);
}

int	builtin_exit(char **argv, t_sh *sh)
{
	long long	exit_status;

	if (!argv[1])
	{
		printf("exit\n");
		exit(0);
	}
	exit_status = ft_atoll(argv[1]);
	if (exit_status < 0)
	{
		if (sh->multi_cmd_flag == 0)
			printf("exit\nminishell: exit: %s: numeric argument required\n", argv[1]);
		else
			printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit(255);
	}
	if (argv[2] != NULL)
	{
		if (sh->multi_cmd_flag == 0)
			printf("minishell: exit: too many arguments\n");
		else
			printf("exit\nminishell: exit: too many arguments\n");
		return (-1);
	}
	printf("exit\n");
	exit_status %= 256;
	exit(exit_status);
}
