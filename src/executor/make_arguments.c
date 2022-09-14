#include "executor.h"
#include <stdlib.h>
#include <stdio.h> //test

void	argvprint(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%d: %s\n", i, argv[i]);
		i++;
	}
}

char	**make_arguments(t_script *script)
{
	char	**result;
	t_token	*token;
	int		i;


	result = (char **)malloc(sizeof(char *) * (script->argc + 1));
	//if (!result) error
	i = 0;
	token = script->cmd;
	while ((i < script->argc) && (token))
	{
		while (token && (token->type > WORD))
			token = token->next;
		result[i++] = token->content;
		token = token->next;
	}
	result[i] = 0;
	argvprint(result);
	return (result);
}
