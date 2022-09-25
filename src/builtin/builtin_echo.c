/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:10:19 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 16:04:41 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
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
