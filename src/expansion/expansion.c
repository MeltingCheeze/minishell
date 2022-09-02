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
static int	expand_tokens(t_sh *sh, t_token *token) // test
{
	// t_token	*token;
	t_type	prev_type;
	int		is_in_file;

	// token = sh->script->cmd;
	prev_type = 0;
	is_in_file = 0;
	while (token)
	{
		if ((prev_type != RD_HEREDOC) && (token->type <= WORD))
			parameter_expansion(sh, token);
		if (is_in_file == 2)
			is_in_file = 1;
		if (token->type == RD_IN)
			is_in_file = 1;
		else if (token->type == RD_HEREDOC)
			is_in_file = 2;
		else if ((token->type == CMD) && cmdpath_expansion(sh, token))
			return (127);
		else if ((is_in_file == TRUE) && input_file_checker(token))
			return (1);
		prev_type = token->type;
		token = token->next;
	}
	return (0);
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
	// 	if (expand_tokens(sh))
	//		 return(1);
	// 	cmd = cmd->next;
	// }
	if (expand_tokens(sh, token))
		return (1);
	return (0);
}
