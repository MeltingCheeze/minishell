/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:54:47 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 13:15:14 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "msh_struct.h"

int		env_init(t_env_info *env_info, char **envp);
int		env_terminate(t_env **env);
t_env	*env_new(char *s);
void	env_add_back(t_env **env, t_env *new);
void	env_del(t_env_info *env_info, char *key);

void	env_print(t_env *env);

char	**make_envp(t_env *env, int env_size);

t_env	*find_env(t_env *env, char *key);
char	*find_env_value(t_env *env, char *key); // 나중에 지우기

int		is_valid_env_first_name(char c);
int		is_valid_env_name(char c);

char	*set_env_key(char *s);
char	*set_env_value(char *s);

void	export_new(t_env_info *env_info, char *envp);

#endif
