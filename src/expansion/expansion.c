#include "expansion.h"

//int   expand_tokens()
//{
	//  [todo] = += 대입연산
	//  3. parameter and variable expansion [$ 매개변수 확장]
	//  5. command substitution [echo $(date +%D)]
	//  6. word splitting
	//  7. filename expansion
//}

// static void	expand_tokens(t_sh *sh)
static void	expand_tokens(t_sh *sh, t_token *token) // test
{
	// t_token	*token;
	t_type	prev_type;

	// token = sh->script->cmd;
	prev_type = 0;
	while (token)
	{
		if ((prev_type != RD_HEREDOC) && (token->type <= WORD))
			parameter_expansion(sh, token);
		// if ((token->type == CMD) && cmdpath_expansion(sh, token))
		// 	return (127);
		// else if (is_filename(prev_type, token) && filename_expansion(sh))
		// 	return (1);
		prev_type = token->type;
		token = token->next;
	}
}

// int expansion(t_sh *sh)
int	expansion(t_sh *sh, t_token *token) // test
{
	// t_script	*cmd;
	// t_token		*t;

	// cmd = sh->script;
	// while (cmd)
	// {
	// 	t = cmd->cmd;
	// 	expand_tokens(sh);
	// 	cmd = cmd->next;
	// }
	expand_tokens(sh, token);
	return (0);
}
