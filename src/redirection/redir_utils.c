/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 15:40:39 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:01:49 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"
#include "redirection.h"
#include "env.h"

void	expand_line(t_env *env, char **dst, char *src)
{
	char	*cur;
	int		len;

	if (*src == 0)
		return ;
	cur = src;
	while (*cur)
	{
		if (*cur == '$')
		{
			len = count_key_len(cur + 1);
			if (*(cur + 1) == '?')
				last_exit_value_expansion(dst);
			else if (len)
				param_expansion(env, dst, src, cur);
			return (expand_line(env, dst, cur + len + 1));
		}
		cur++;
	}
	*dst = attach_str(*dst, src);
}
