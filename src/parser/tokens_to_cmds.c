#include "parser.h"

// 이거 draft 임

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

void	tokens_to_cmds(t_sh *sh, t_token *token)
{
	t_token		*cur;
	t_token		*base;
	t_token		*next;
	t_script	*new;
	int			argc;
	int			herecnt;

	sh->script = 0;
	cur = token;
	while (cur)
	{
		argc = 0;
		herecnt = 0;
		if (cur->type <= WORD)
			argc++;
		else if (cur->type == RD_HEREDOC)
			herecnt++;
		base = cur;
		while (cur->next && (cur->next->type != PIPE))
		{
			cur = cur->next;
			if (cur->type <= WORD)
				argc++;
			else if (cur->type == RD_HEREDOC)
				herecnt++;
		}
		new = scriptnew(base, argc, herecnt);
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
