/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:18:33 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 20:52:53 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

static void	numeric_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_last_exit_value = 255;
	exit(255);
}

static int	ft_atoll_sub(char *str)
{
	int	result;
	int	length;
	int	i;

	i = 0;
	length = 0;
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
	return (result);
}

static int	ft_atoll(char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
		if (str[i] == '\0')
			numeric_error(str);
	}
	result = ft_atoll_sub(&str[i]);
	if (result < 0)
		numeric_error(str);
	return (result * sign);
}

int	builtin_exit(char **argv, t_sh *sh)
{
	long long	exit_status;

	if (sh->multi_cmd_flag != 1)
		ft_putstr_fd("exit\n", 1);
	if (!argv[1])
		exit(g_last_exit_value);
	if (!ft_strcmp("-1", argv[1]))
		exit(-1);
	exit_status = ft_atoll(argv[1]);
	if (argv[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	g_last_exit_value = exit_status;
	exit(exit_status);
}
