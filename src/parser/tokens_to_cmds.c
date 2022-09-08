#include "parser.h"
#include "libft.h" // 나중에 고치기
#include <stdio.h> // 나중에 지우기

// 이거 draft 임

static t_script	*scriptnew(t_token *cmd, int argc)
{
	t_script	*new;

	new = (t_script *)malloc(sizeof(t_script));
	new->cmd = cmd;
	new->next = 0;
	new->fd_in = 0;
	new->fd_out = 1;
	new->argc = argc;
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

//void	tokens_to_cmds(t_sh *sh, t_token *token)
//{
//	t_token		*prev;
//	t_token		*cur;
//	t_token		*next;
//	t_script	*new;

//	sh->script = 0;
//	prev = 0;
//	cur = token;
//	while (cur)
//	{
//		if (cur->type == CMD)
//		{
//			new = scriptnew(cur);
//			scriptadd_back(&sh->script, new);
//			if (prev)
//				prev->next = 0;
//		}
//		while (cur->next && (cur->next->type != PIPE))
//			cur = cur->next;
//		prev = cur;
//		cur = cur->next;
//		if (cur)
//		{
//			next = cur->next;
//			if (cur->type == PIPE)
//			{
//				free(cur->content);
//				cur->content = 0;
//				free(cur);
//			}
//		}
//		else
//			next = 0;
//		cur = next;
//	}
//}

void	tokens_to_cmds(t_sh *sh, t_token *token)
{
	t_token		*cur;
	t_token		*base;
	t_token		*next;
	t_script	*new;
	int			argc;

	sh->script = 0;
	cur = token;
	while (cur)
	{
		argc = 0;
		if (cur->type <= WORD)
			argc++;
		base = cur;
		while (cur->next && (cur->next->type != PIPE))
		{
			cur = cur->next;
			if (cur->type <= WORD)
				argc++;
		}
		new = scriptnew(base, argc);
		scriptadd_back(&sh->script, new);
		base = cur;
		cur = cur->next;
		if (cur)
		{
			base->next = 0;
			next = cur->next;
			free(cur->content);
			cur->content = 0;
			free(cur);
		}
		else
			next = 0;
		cur = next;
	}
}
