#include "expansion.h"

char	*do_expand(t_env *env, char *joined, char **start, char **cur)
{
	char	*not_expand;
	char	*key;
	char	*value;

	// 예시 : "abc$USER.sdf$AAA+fjew" (do_expand()이 2번 호출됨)
	if (!joined && (*start != *cur))
		// (1 호출) joined = "abc"
		joined = ft_substr(*start, 0, *cur - *start);
	else
	{
		// (2 호출) not_expand = ".sdf"
		not_expand = ft_substr(*start, 0, *cur - *start);
		joined = attach_str(joined, not_expand);
		free(not_expand);
	}
	key = (*cur + 1);
	if (*key)
	{
		value = find_env_value(env, key);
		free(key);
		if (value)
			// (1 호출) $USER = "chaejkim"
			joined = attach_str(joined, value);
		// else
			// (2 호출) $AAA = "\0"
	}
	// (1 호출) start = ".sdf$AAA+fjew"
	// (2 호출) start = "+fjew" -> param_expansion()에서 do_expand 후, if(start) 에서 걸림
	*start = *cur + ft_strlen(key) + 1;
	*cur = *start - 1;
	return (joined);
}

