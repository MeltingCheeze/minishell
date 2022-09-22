/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:18:49 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/22 22:22:52 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "libft.h"
#include "utils.h"

void	last_exit_value_expansion(char **dst)
{
	*dst = attach_str(*dst, ft_itoa(g_last_exit_value));
}

void	param_expansion(t_env *env, char **dst, char *src, char *cur)
{
	*dst = attach_param_prestr(*dst, src, cur);
	*dst = attach_param_str(env, *dst, cur);
}

static void	param_expansion_in_quote(t_env *env,
	char **dst, char *src, char *cur)
{
	*dst = attach_param_prestr(*dst, src, cur);
	*dst = attach_str(*dst, "\"");
	*dst = attach_param_str(env, *dst, cur);
	*dst = attach_str(*dst, "\"");
}

static void	check_content(t_env *env, char **dst, char *src, char *cur)
{
	char	quote;
	int		len;

	quote = 0;
	if (*src == 0)
		return ;
	while (*cur)
	{
		if (*cur == '"' || *cur == '\'')
			quote = set_quote(quote, *cur);
		else if (quote != '\'' && *cur == '$')
		{
			len = count_key_len(cur + 1);
			if (*(cur + 1) == '?')
				last_exit_value_expansion(dst);
			else if (len && quote == '"')
				param_expansion(env, dst, src, cur);
			else if (len && quote == 0)
				param_expansion_in_quote(env, dst, src, cur);
			return (check_content(env, dst, cur + len + 1, cur + len + 1));
		}
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
				check_content(env, &expanded, token->content, token->content);
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
