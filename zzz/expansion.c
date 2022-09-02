#include "expansion.h"

//int   expand_tokens()
//{
	//  [todo] = += 대입연산
	//  3. parameter and variable expansion [$ 매개변수 확장]
	//  5. command substitution [echo $(date +%D)]
	//  6. word splitting
	//  7. filename expansion
//}

static void	expand_tokens(t_sh *sh)
{
	t_token	*cur;
	char	*new;
	t_type	pre;

	cur = sh->script;
	pre = 0;
	while (cur)
	{
		new = 0;
		if (pre != RD_HEREDOC && (cur->type <= WORD))
		{
			parameter_expansion(sh, cur->content);
			if ((cur->type == CMD) && cmdpath_expansion(sh))
				return (127);
			else if (cur->type == WORD && filename_expansion(sh))
				return (1);
		}
		pre = cur->type;
		cur = cur->next;
	}
}

int expansion(t_sh *sh)
{
	t_script	*cmd;
	t_token		*t;

	cmd = sh->script;
	while (cmd)
	{
		t = cmd->cmd;
		expand_tokens(sh);
		cmd = cmd->next;
	}

}

