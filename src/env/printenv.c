#include "env.h"
#include <stdio.h>

void	envprint(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}