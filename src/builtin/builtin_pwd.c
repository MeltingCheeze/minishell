/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:19:50 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 18:09:46 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int	builtin_pwd(t_sh *sh)
{
	printf("%s\n", sh->cur_pwd);
	return (0);
}
