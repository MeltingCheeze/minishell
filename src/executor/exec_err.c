/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:33:11 by hyko              #+#    #+#             */
/*   Updated: 2022/09/22 21:16:21 by hyko             ###   ########.fr       */
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

int	execute_error(char *cmd)
{
	if (!ft_strcmp(cmd, "."))
	{
		err_msg(cmd, "filename argument required\n.: usage: . filename [arguments]");
		return (2);
	}
	else if (!is_path(cmd))
	{
		err_msg(cmd, CMD_NOT_FOUND_MSG);
		return (127);
	}
	else if (is_file_exists(cmd))
	{
		if (!*(strrchr(cmd, '/') + 1))
			err_msg(cmd, "is a directory");
		else
			err_msg(cmd, strerror(errno));
		return (126);
	}
	else if (!is_file_exists(cmd)) // 이거 나중에 else로 바꾸기
	{
		err_msg(cmd, "No such file or directory");
		return (127);
	}
	else
		ft_putendl_fd("Undefined Behavior", STDERR_FILENO);       // 이거 나중에 없애기
	return (1);
}
