#include "minishell.h"
#include "libft.h"

//int   expand_tokens()
//{
	//  [todo] = += 대입연산
	//  3. parameter and variable expansion [$ 매개변수 확장]
	//  5. command substitution [echo $(date +%D)]
	//  6. word splitting
	//  7. filename expansion
//}

void	expand_tokens(t_token **token)
{
	t_token	*pre;
	t_token	*cur;
	char	*new;

	cur = *token;
	pre = 0;
	while (cur)
	{
		new = 0;
		RD_HEREDOC
		if (!pre
			|| ((pre && (pre->type != RD_HEREDOC)) && (cur->type <= FILENAME)))
		{
			new = cur->content;
			while (new)
			{
				new = ft_strchr(cur->content, '$');
				parameter_expansion();
			}
			if ((cur->type == CMD) && cmdpath_expansion())
				return (127);
			else if (cur->type == CMD && filename_expansion())
				return (1);
		}
		pre = cur;
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
		expand_tokens();
		cmd = cmd->next;
	}

}

