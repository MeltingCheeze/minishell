/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:52:10 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 16:41:45 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <unistd.h>

# include "msh_struct.h"
# include "env.h"
# include "libft.h"

# define SHELL_NAME "minishell: "
# define FILE_NOT_FOUND 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_FOUND_MSG "command not found"
# define FILE_NOT_FOUND_MSG "No such file or directory"
# define READ 0
# define WRITE 1

/* execute */
int			execute(t_sh *sh);

/* exec_builtin */
t_builtin	is_builtin(t_token *token);
int			execve_builtin(char **argv, t_sh *sh, t_builtin builtin);

/* exec_child */
void		child_process(t_sh *sh, t_script *cur_cmd, int *pipeline);

/* exec_parent */
void		parent_process(t_script *cur_cmd, int *pipeline, int *std_dup);

/* exec_utils */
char		**make_arguments(t_script *script);
char		*cmd_to_path(t_sh *sh, t_token *token);
int			is_path(char *s);

/* exec_err */
int			execute_error(char *cmd);

#endif
