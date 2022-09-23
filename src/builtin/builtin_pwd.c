/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:19:50 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:42:42 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, BUFFER_SIZE);
	if (!buf)
		return (errno);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
