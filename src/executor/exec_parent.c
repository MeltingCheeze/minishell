/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:58:29 by hyko              #+#    #+#             */
/*   Updated: 2022/09/22 20:16:19 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtin.h"
#include <sys/types.h> 
#include <sys/wait.h>

void	parent_process(t_script *cur_cmd, int *pipeline, int *std_dup)
{
	if (cur_cmd->next != NULL)
	{
		close(pipeline[WRITE]);
		dup2(pipeline[READ], STDIN_FILENO);
		close(pipeline[READ]);
	}
	else
	{
		dup2(std_dup[0], STDIN_FILENO);
		dup2(std_dup[1], STDOUT_FILENO);
		close(std_dup[0]);
		close(std_dup[1]);
	}
}
