/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:44:37 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:44:38 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

void	ft_error(char *msg)
{
	char	*str_errno;

	str_errno = ft_strjoin(msg, strerror(errno));
	perror(str_errno);
	exit(EXIT_FAILURE);
}
