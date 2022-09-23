/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:21:02 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 12:40:59 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "minishell.h"
#include <string.h>
#include <errno.h>
#define SHELL_NAME "minishell: "

int	open_error(char *fname)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(fname, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
