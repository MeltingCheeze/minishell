/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:45:05 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/22 22:17:32 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_cnt(t_type type, int *argc, int *herecnt)
{
	if (type <= WORD)
		(*argc) += 1;
	else if (type == RD_HEREDOC)
		(*herecnt) += 1;
}

static t_token	*find_tail(t_token *token, int *argc, int *herecnt)
{
	while (token->next && (token->next->type != PIPE))
	{
		token = token->next;
		set_cnt(token->type, argc, herecnt);
	}
	return (token);
}

static void	del_pipetkn(t_token **pipetkn, t_token *tail)
{
	tail->next = 0;
	free((*pipetkn)->content);
	(*pipetkn)->content = 0;
	free(*pipetkn);
	*pipetkn = 0;
}

void	tokens_to_cmds(t_sh *sh, t_token *token)
{
	t_token	*head;
	t_token	*tail;
	int		argc;
	int		herecnt;

	sh->script = 0;
	while (token)
	{
		argc = 0;
		herecnt = 0;
		set_cnt(token->type, &argc, &herecnt);
		head = token;
		tail = find_tail(token, &argc, &herecnt);
		add_script(&sh->script, head, argc, herecnt);
		token = tail->next;
		if (token)
		{
			head = token->next;
			del_pipetkn(&token, tail);
		}
		else
			head = 0;
		token = head;
	}
}
