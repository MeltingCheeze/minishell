#include "minishell.h"

//int	expand_tokens()
//{
	//	[todo] = += 대입연산
	//	3. parameter and variable expansion [$ 매개변수 확장]
	//	5. command substitution [echo $(date +%D)]
	//	6. word splitting
	//	7. filename expansion
//}

int	parse(t_script *script, char *line)
{
	t_token	*token;

	(void)script;
	token = tokenizer(line); //1. Devide the input into *tokens* (words and operators)
	//tokens_to_cmds();   //2. Parse these tokens into commands and *other constructs* ()
	//expand_tokens();
	tokenclear(&token);
	return (0);
}
