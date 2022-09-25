/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:44:59 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/25 16:08:04 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"
#include "expansion.h"
#include "libft.h"

static int	valid_quote(char *line)
{
	char	quote;

	quote = 0;
	while (*line)
	{
		if (!quote && (*line == '\'' || *line == '"'))
		{
			quote = *line;
			while (quote && *(line + 1))
			{
				line++;
				if (*line == quote)
					quote = 0;
			}
		}
		line++;
	}
	if (quote)
	{
		ft_putstr_fd("minishell: syntax error quote opened\n", STDERR_FILENO);
		g_last_exit_value = 258;
		return (1);
	}
	return (0);
}

int	parser(t_sh *sh, char *line)
{
	t_token	*token;

	(void)sh;
	if (valid_quote(line))
		return (1);
	if (tokenizer(&token, line) != 0 || !token || lexcial_analyze(token) != 0)
	{
		tokenclear(&token);
		return (1);
	}
	tokens_to_cmds(sh, token);
	expand_and_rm_quote(sh->script, sh->env_info.head);
	return (0);
}
