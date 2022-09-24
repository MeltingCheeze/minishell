/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:10:19 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 19:19:16 by chaejkim         ###   ########.fr       */
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
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0) // 수정 필요!!!!!!!!
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
