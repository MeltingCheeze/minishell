#include "env.h"
#include "libft.h"
#include <stdio.h>

#define SHELL_NAME "minishell: "

static int	env_err(void)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("env: wrong number of arguments\n", 2);
	ft_putstr_fd("usage: env\n", 2);
	return (1);
}

static void	envp_print(char	**envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

int	builtin_env(char **argv, t_env_info *env_info)
{
	t_env	*new;

	++argv;
	if (*argv && **argv)
		return (env_err());
	envp_print(env_info->envp);
	return (0);
}
