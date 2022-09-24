/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:54:55 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 18:24:40 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "msh_struct.h"
# include "env.h"

int		expansion(t_script *script, t_env *env);
void	last_exit_value_expansion(char **dst, char *src, char *cur);
void	param_expansion(t_env *env, char **dst, char *src, char *cur);

char	*attach_str(char *joined, char *expand);
char	*attach_param_prestr(char *joined, char *start, char *cur);
char	*attach_param_str(t_env *env, char *joined, char *cur);
int		count_key_len(char *str);

#endif
