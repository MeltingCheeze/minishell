#include "expansion.h"

static int	expand_tokens(t_sh *sh, t_script *script)
{
	t_token	*token;
	char	*cmd;
	int		is_in_file;

	token = script->cmd;
	is_in_file = 0;
	cmd = 0;
	while (token)
	{
		if ((is_in_file != RD_HEREDOC) && (token->type <= WORD))
			parameter_expansion(sh, token);
		if ((is_in_file == RD_HEREDOC) || (token->type == RD_IN))
			is_in_file = TRUE;
		else if (token->type == RD_HEREDOC)
			is_in_file = RD_HEREDOC;
		else if ((token->type == CMD) && cmdpath_expansion(sh, token))
			return (127);
		else if ((is_in_file == TRUE) && input_file_checker(sh, cmd, token))
			return (1);
		if (token->type == CMD)
			cmd = token->content;
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
