/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:18:49 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/25 14:22:17 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"
#include "utils.h"

void	last_exit_value_expansion(char **dst, char *src, char *cur)
{
	char	*exit_value;

	*dst = attach_param_prestr(*dst, src, cur);
	exit_value = ft_itoa(g_last_exit_value);
	*dst = attach_str(*dst, exit_value);
	free(exit_value);
}

void	param_expansion(t_env *env, char **dst, char *src, char *cur)
{
	*dst = attach_param_prestr(*dst, src, cur);
	*dst = attach_param_str(env, *dst, cur);
}

static void	check_content(t_env *env, char **dst, char *src, char quote)
{
	char	*cur;
	int		len;

	if (*src == 0)
		return ;
	cur = src;
	while (*cur)
	{
		if (!quote && (*cur == '"' || *cur == '\''))
		{
			quote = *cur;
			*dst = attach_param_prestr(*dst, src, cur);
			//if (cur != src)
			//	*dst = attach_param_prestr(*dst, src, cur);
			return (check_content(env, dst, cur + 1, quote));
		}
		else if (*cur == '"' || *cur == '\'')
		{
			if (quote == *cur)
			{
				quote = 0;
				*dst = attach_param_prestr(*dst, src, cur);
				//if (cur - 1 != src)
				//	*dst = attach_param_prestr(*dst, src, cur - 1);
				return (check_content(env, dst, cur + 1, quote));
			}
		}
		else if (*cur == '$')
		{
			len = count_key_len(cur + 1);
			if (*(cur + 1) == '?')
				last_exit_value_expansion(dst, src, cur);
			else if (len && quote != '\'')
				param_expansion(env, dst, src, cur);
			return (check_content(env, dst, cur + len + 1, quote));
		}
		if (*cur)
			cur++;
	}
	*dst = attach_str(*dst, src);
}

int	expansion(t_script *script, t_env *env)
{
	t_token		*token;
	char		*expanded;

	while (script)
	{
		token = script->head;
		while (token)
		{
			expanded = 0;
			if (token->type <= WORD)
			{
				check_content(env, &expanded, token->content, 0);
				if (expanded)
				{
					free(token->content);
					token->content = expanded;
				}
			}
			token = token->next;
		}
		script = script->next;
	}
	return (0);
}
