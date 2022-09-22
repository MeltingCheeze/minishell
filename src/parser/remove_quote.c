/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:45:01 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/22 22:17:25 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	rm_token_quote(char *dest, char *src, char quote)
{
	while (*src)
	{
		if (*src == '\'' || *src == '"')
		{
			quote = *src;
			src++;
			while (*src != quote)
				*(dest++) = *(src++);
			quote = 0;
			src++;
		}
		else
			*(dest++) = *(src++);
	}
	*dest = *src;
}

static void	rm_cmd_quote(t_token *cmd)
{
	while (cmd)
	{
		rm_token_quote(cmd->content, cmd->content, 0);
		cmd = cmd->next;
	}
}

void	remove_quote(t_script *script)
{
	while (script)
	{
		rm_cmd_quote(script->head);
		script = script->next;
	}
}
