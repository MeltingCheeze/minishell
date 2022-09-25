/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:17:51 by chaejkim          #+#    #+#             */
/*   Updated: 2022/09/25 18:27:31 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_struct.h"
#include "stdlib.h"

static t_script	*scriptnew(t_token *cmd, int argc, int herecnt)
{
	t_script	*new;

	new = (t_script *)malloc(sizeof(t_script));
	new->head = cmd;
	new->next = 0;
	new->fd_in = 0;
	new->fd_out = 1;
	new->argc = argc;
	new->herecnt = herecnt;
	return (new);
}

static void	scriptadd_back(t_script **script, t_script *new)
{
	t_script	*cur;

	if (*script == NULL)
	{
		*script = new;
		return ;
	}
	cur = *script;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

void	add_script(t_script **script, t_token *head, int argc, int herecnt)
{
	t_script	*new;

	new = scriptnew(head, argc, herecnt);
	scriptadd_back(script, new);
}

// void	clear_script()
