/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:54:44 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:55:50 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

int		builtin_export(char **argv, t_env_info *env_info);
void	no_argv_print(t_env_info *env_info);

int		builtin_env(char **argv, t_env_info *env_info);

int		builtin_unset(char **argv, t_env_info *env_info);

int		builtin_echo(char **argv);
int		builtin_pwd(void);
int		builtin_cd(char **argv, t_env_info *env_info);
int		builtin_exit(char **argv, t_sh *sh);

#endif
