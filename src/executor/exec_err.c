/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:33:11 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 20:53:04 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "libft.h"
#include "utils.h"
#include <string.h>
#include <errno.h>

static void	err_msg(char *content, char *msg)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(content, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

static int	errno_to_exit_value(int err)
{
	if (err == ENOENT)
		return (127);
	return (126);
}

int	execute_error(char *cmd)
{
	if (!is_path(cmd))
	{
		err_msg(cmd, CMD_NOT_FOUND_MSG);
		return (127);
	}
	else if (is_directory(cmd))
	{
		err_msg(cmd, "is a directory");
		return (126);
	}
	err_msg(cmd, strerror(errno));
	return (errno_to_exit_value(errno));
}
