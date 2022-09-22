#include "parser.h"
#include "expansion.h"
#include "libft.h"
#include "minishell.h" //test print

//tokenprint(token);
//print_type(token);
//scriptprint(sh->script);

static int	valid_quote(char *line)
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
	if (quote)
	{
		ft_putstr_fd("minishell: syntax error quote opened\n", STDERR_FILENO);
		g_last_exit_value = 258;
		return (1);
	}
	return (0);
}

int	parser(t_sh *sh, char *line)
{
	t_token	*token;
	t_list	*expand_lst;

	(void)sh;
	if (valid_quote(line))
		return (1);
	if (tokenizer(&token, line) != 0 || lexcial_analyze(token) != 0)
	{
		tokenclear(&token);
		return (1);
	}
	tokens_to_cmds(sh, token);
	expansion(sh);
	remove_quote(sh->script);
	return (0);
}
