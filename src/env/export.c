#include "env.h"
#include "libft.h"
#include <stdio.h> //test

// 1, 2, 3
void	export_new(t_env_info *env_info, char *envp)
{
	t_env	*new_env;
	char	*key;
	char	*value;

	if (*envp == '_' && *(envp + 1) == '\0')
		return ; // 이거 어떻게 할지 모르겠음
	key = getkey(envp);
	new_env = find_env(env_info->head, key);
	if (new_env)
	{
		value = getvalue(envp);
		printf("key : %s, new_env->value : %s\n", key, new_env->value);
		if (new_env->value)
			free(new_env->value);
		new_env->value = value;
	}
	else
	{
		new_env = envnew(envp);
		envadd_back(&env_info->head, new_env);
	}
		
	free(key);
	env_info->size++;
}
