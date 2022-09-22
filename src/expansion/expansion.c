#include "expansion.h"
#include "libft.h"
#include "utils.h"

void	last_exit_value_expansion(char **dst)
{
	*dst = attach_str(*dst, ft_itoa(g_last_exit_value));
}

void	param_expansion(t_env *env, char **dst, char *src, char *cur)
{
	*dst = attach_param_prestr(*dst, src, cur);
	*dst = attach_param_str(env, *dst, cur);
}

static void	param_expansion_in_quote(t_env *env, char **dst, char *src, char *cur)
{
	*dst = attach_param_prestr(*dst, src, cur);
	*dst = attach_str(*dst, "\"");
	*dst = attach_param_str(env, *dst, cur);
	*dst = attach_str(*dst, "\"");
}

static void	check_content(t_env *env, char **dst, char *src, char *cur)
{
	char	quote;
	int		len;

	quote = 0;
	if (*src == 0)
		return ;
	while (*cur)
	{
		if (*cur == '"' || *cur == '\'')
			quote = set_quote(quote, *cur);
		else if (quote != '\'' && *cur == '$')
		{
			len = count_key_len(cur + 1);
			if (*(cur + 1) == '?')
				last_exit_value_expansion(dst);
			else if (len && quote == '"')
				param_expansion(env, dst, src, cur);
			else if (len && quote == 0)
				param_expansion_in_quote(env, dst, src, cur);
			return (check_content(env, dst, cur + len + 1, cur + len + 1));
		}
		cur++;
	}
	*dst = attach_str(*dst, src);
}

int	expansion(t_sh *sh)
{
	t_script	*script;
	t_token		*token;
	char		*expand_str;

	script = sh->script;
	while (script)
	{
		token = script->head;
		while (token)
		{
			expand_str = 0;
			if (token->type <= WORD)
			{
				check_content(sh->env_info.head, &expand_str, token->content, token->content);
				if (expand_str)
				{
					free(token->content);
					token->content = expand_str;
				}
			}
			token = token->next;
		}
		script = script->next;
	}
	return (0);
}
