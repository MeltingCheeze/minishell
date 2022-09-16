#include "builtins.h"
#include "libft.h"
#include "env.h"
#include <stdio.h>

int	builtin_cd(char **argv, t_env_info *env_info)
{
	char	*path;

	path = argv[1];
	if (!path || !ft_strcmp(path, "~") || !ft_strcmp(path, "~/")) // $HOME
		path = find_env_value(env_info->head, "HOME");
	if (chdir(path) < 0) // 실패
	{
		printf("cd: %s: no such file or directory\n", path);
		return (-1);
	}
	else // 성공 -> env $PWD, $OLDPWD 변경
	{
		/*
		기존 PWD -> $OLDPWD
		현재 PWD(getcwd()) -> $PWD
		*/
		return (0);
	}
}
