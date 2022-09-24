/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:19:50 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 20:13:15 by chaejkim         ###   ########.fr       */
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
	if (!buf)						// 수정필요 !!! (cd a/b ; rm -r ../../a ; pwd)
		return (errno);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
