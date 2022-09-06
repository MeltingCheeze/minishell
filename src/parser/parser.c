#include "parser.h"
#include "libft.h" // 나중에 고치기
#include "minishell.h" // 나중에 지우기
int	expansion(t_sh *sh); // 나중에 고치기

static int	quote_err(int *exit_value)
{
	ft_putstr_fd("minishell: syntax error quote opened\n", STDERR_FILENO);
	*exit_value = 258;
	return (258);
}

static int	is_valid_quote(char *line)
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

	(void)sh;
	if (is_valid_quote(line) && quote_err(&sh->last_exit_value))
		return (1);
	token = tokenizer(line);
	if (token == NULL || lexcial_analyze(token))
		return (1);
	//tokenprint(token);
	//print_type(token);
	tokens_to_cmds(sh, token);
	//printf("before expasion\n");
	//tokenprint(token);
	//scriptprint(sh->script);
	expansion(sh);
	//printf("after expasion\n");
	//scriptprint(sh->script);
	remove_quote(sh->script);
	scriptprint(sh->script);
	return (0);
}
