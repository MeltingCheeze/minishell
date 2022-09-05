#include "struct.h"
#include <stdio.h>

void	envprint(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		printf("\033[0;33m%s\033[0m=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}

void	tokenprint(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		printf("\033[0;33m%s\033[0m\n", cur->content);
		cur = cur->next;
	}
}

void	print_type(t_token *token)
{
	t_token *curr;

	curr = token;
	while (curr)
	{
		printf("content : %s  | type : %d\n", curr->content, curr->type);
		curr = curr->next;
	}
	printf("=======================\n");
}

void	scriptprint(t_script *script)
{
	t_script	*cur;

	cur = script;
	while (cur)
	{
		tokenprint(cur->cmd);
		printf("=============\n");
		cur = cur->next;
	}
}
