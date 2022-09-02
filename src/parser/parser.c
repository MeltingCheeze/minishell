#include "parser.h"
#include "libft.h" // 나중에 고치기
#include "minishell.h" // 나중에 지우기
int	expansion(t_sh *sh, t_token *token); // test

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
		if (!quote && (*line == SINGLE || *line == DOUBLE))
		{
			quote = *line;
			while (quote && *(line + 1))
			{
				line++;
				if (*line == quote)
				{
					quote = 0;
					break ;
				}
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
	// envprint(sh->env);
	if (is_valid_quote(line) && quote_err(&sh->last_exit_value))
		return (1);
	token = tokenizer(line); //1. Devide the input into *tokens* (words and operators)
	if (token == NULL)
		return (1);
	else
	{
		// expansion(sh);
		expansion(sh, token); // test
		tokenprint(token);
	}
	// lexcial_analyze(token);
	// print_type(token);
	// tokens_to_cmds();   //2. Parse these tokens into commands and *other constructs* ()
	// expand(script);
	// quote removal(&token);
	return (0);
}
