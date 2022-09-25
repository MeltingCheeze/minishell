/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:18:49 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/25 20:15:00 by hyko             ###   ########.fr       */
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
	if (*(cur + 1) == '?')
		last_exit_value_expansion(dst, src, cur);
	else
	{
		*dst = attach_param_prestr(*dst, src, cur);
		*dst = attach_param_str(env, *dst, cur);
	}
}

static void	check_content(t_env *env, char **dst, char *src, char quote)
{
	char	*cur;
	int		len;

	cur = src;
	while (*cur)
	{
		if ((*cur == '"' || *cur == '\'') && (!quote || quote == *cur))
		{
			quote = set_quote(quote, *cur);
			*dst = attach_param_prestr(*dst, src, cur);
			check_content(env, dst, cur + 1, quote);
			return ;
		}
		else if (*cur == '$' && quote != '\'')
		{
			len = count_key_len(cur + 1);
			if (len)
				param_expansion(env, dst, src, cur);
			check_content(env, dst, cur + len + 1, quote);
			return ;
		}
		cur++;
	}
	*dst = attach_str(*dst, src);
}

int	expand_and_rm_quote(t_script *script, t_env *env)
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
