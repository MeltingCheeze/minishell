#include "expansion.h"

//int   expand_tokens()
//{
	//  [todo] = += 대입연산
	//  3. parameter and variable expansion [$ 매개변수 확장]
	//  5. command substitution [echo $(date +%D)]
	//  6. word splitting
	//  7. filename expansion
//}

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
		if ((is_in_file != 2) && (token->type <= WORD))
			parameter_expansion(sh, token);
		if ((is_in_file == 2) || (token->type == RD_IN))
			is_in_file = 1;
		else if (token->type == RD_HEREDOC)
			is_in_file = 2;
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
