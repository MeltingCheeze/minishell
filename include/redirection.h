/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 11:45:39 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:55:03 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <unistd.h>

# include "struct.h"
# include "libft.h"

# define SHELL_NAME "minishell: "
# define FILE_NOT_FOUND 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_FOUND_MSG "command not found"
# define FILE_NOT_FOUND_MSG "No such file or directory"
# define READ 0
# define WRITE 1

/* redirection */
int		redirection(t_script *cur_cmd);

/* redir_heredoc */
void	heredoc_read_line(t_sh *sh);

/* redir_err */
int		open_error(char *fname);

/* redir_utils */
void	expand_line(t_env *env, char **dst, char *src);

#endif
