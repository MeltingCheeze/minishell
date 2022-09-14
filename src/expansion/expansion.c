#include "expansion.h"

static int	expand_tokens(t_sh *sh, t_script *script)
{
	t_token	*token;
	char	*cmd;

	token = script->cmd;
	cmd = 0;
	while (token)
	{
		if (token->type <= WORD)
			parameter_expansion(sh, token);
		token = token->next;
	}
	return (0);
}

int expansion(t_sh *sh)
{
	t_script	*script;

	script = sh->script;
	while (script)
	{
		if (expand_tokens(sh, script))
			return(1);
		script = script->next;
	}
	return (0);
}
