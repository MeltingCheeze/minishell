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
		if (length > 19) //exit 인자가 long long 범위 벗어나면 error처리 해야하는데 정확한 값 비교하기 힘들어서 그냥 자릿수로 비교함
			return (-1);
	}
	return (result * sign);
}

int	builtin_exit(char **argv,t_sh *sh)
{
	long long	exit_status;

	if (sh->multi_cmd_flag != 1)
		ft_putstr_fd("exit\n", 1);
	if (!argv[1]) //exit 뒤에 인자 없을 때 -> exit(0)으로 처리
		exit(0);
	exit_status = ft_atoll(argv[1]);
	if (exit_status < 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (argv[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-1);
	}
	exit_status %= 256;
	exit(exit_status);
}
