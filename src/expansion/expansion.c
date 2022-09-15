#include "expansion.h"
#include "parser.h"
#include <stdio.h> // test
#include "minishell.h" // test

static void	parameter_expansion(t_env *env, t_token **token)
{
	char	*start;
	char	*cur;
	char	*result;
	char	has;

	has = 0;
	result = 0;
	cur = (*token)->content;
	start = cur;
	while (*cur)
	{
		if (!has && (*cur == '"' || *cur == '\''))
			has = *cur;
		else if (has == *cur)
			has = 0;
		else if (has == 0 && *cur == '$' && is_valid_env_name(*(cur + 1)))
		{
			result = attach_str(result, "\"");
			result = do_expand(env, result, &start, &cur); // word_splitting 할꺼면 여기서 해야함 (하지 말자 헿...)
			result = attach_str(result, "\"");
		}
		else if (has == '"' && *cur == '$' && is_valid_env_name(*(cur + 1)))
			result = do_expand(env, result, &start, &cur);
		cur++;
	}
	if (start)
		result = attach_str(result, start);
	if (!result)
		return ;
	free((*token)->content);
	(*token)->content = result;
}

static int	expand_tokens(t_sh *sh, t_script *script)
{
	t_token	*token;
	char	*cmd;

	token = script->head;
	cmd = 0;
	while (token)
	{
		if (token->type <= WORD)
			parameter_expansion(sh->env_info.head, &token);
		token = token->next;
	}
	return (0);
}

int	expansion(t_sh *sh)
{
	t_script	*script;

	script = sh->script;
	while (script)
	{
		if (expand_tokens(sh, script))
			return (1);
		script = script->next;
	}
	return (0);
}
