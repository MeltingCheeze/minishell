#include "parser.h"
#include "expansion.h"
#include "libft.h"
#include "minishell.h" //test print

//tokenprint(token);
//print_type(token);
//scriptprint(sh->script);

static int	quote_err(void)
{
	ft_putstr_fd("minishell: syntax error quote opened\n", STDERR_FILENO);
	// g_last_exit_value = 258;
	return (258);
}

static int	is_unvalid_quote(char *line)
{
	char	quote;

	quote = 0;
	while (*line)
	{
		if (!quote && (*line == '\'' || *line == '"'))
		{
			quote = *line;
			while (quote && *(line + 1))
			{
				line++;
				if (*line == quote)
					quote = 0;
			}
		}
		line++;
	}
	return (quote);
}

int	parser(t_sh *sh, char *line)
{
	t_token	*token;
	t_list	*expand_lst;

	(void)sh;
	if (is_unvalid_quote(line) && quote_err())
		return (258);
	token = tokenizer(line);
	if (token == NULL || lexcial_analyze(token))
		return (1);
	tokens_to_cmds(sh, token);
	expansion(sh);
	remove_quote(sh->script);
	return (0);
}
