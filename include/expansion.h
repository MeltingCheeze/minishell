/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:54:55 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:54:57 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "struct.h"
# include "env.h"

int		expansion(t_script *script, t_env *env);
void	last_exit_value_expansion(char **dst);
void	param_expansion(t_env *env, char **dst, char *src, char *cur);

char	*attach_str(char *joined, char *expand);
char	*attach_param_prestr(char *joined, char *start, char *cur);
char	*attach_param_str(t_env *env, char *joined, char *cur);
int		count_key_len(char *str);

#endif
