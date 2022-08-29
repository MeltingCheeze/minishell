#include "minishell.h"

//int	expand_tokens()
//{
	//  [todo] = += 대입연산
	//  3. parameter and variable expansion [$ 매개변수 확장]
	//  5. command substitution [echo $(date +%D)]
	//  6. word splitting
	//  7. filename expansion
//}

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


int	parse(t_script *script, char *line)
{
	t_token	*token;

	(void)script;
	if (is_valid_quote(line) == 0)
	{
		ft_putstr_fd("minishell: syntax error unclosed quote\n", 2);
		return (1);
	}
	token = tokenizer(line); //1. Devide the input into *tokens* (words and operators)
	// if (token && (*token == NULL))
	// 	return (1);
	//if (token == NULL)
	//  return (1);
	//tokens_to_cmds();   //2. Parse these tokens into commands and *other constructs* ()
	// expand(script);
	//tokenclear(&token);
	return (0);
}

