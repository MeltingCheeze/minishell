#include "parser.h"

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
	return (!quote);
}

int	parser(t_script *script, char *line)
{
	t_token	*token;

	(void)script;
	if (is_valid_quote(line) == 0)
	{
		ft_putstr_fd("minishell: syntax error unclosed quote\n", 2);
		return (1);
	}
	token = tokenizer(line); //1. Devide the input into *tokens* (words and operators)
	if (token == NULL)
		return (1);
	// if (token && (*token == NULL))
	// 	return (1);
	lexcial_analyze(token);
	print_type(token);
	//tokens_to_cmds();   //2. Parse these tokens into commands and *other constructs* ()
	// expand(script);
	//tokenclear(&token);
	return (0);
}
