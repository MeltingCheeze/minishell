#include "env.h"
#include "libft.h"
#include <errno.h> // test
#include <string.h> // test

#define SHELL_NAME "minishell: "


int	env_err(void)
{
	// g_last_return_status = 1;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("env: wrong number of arguments\n", 2);
	ft_putstr_fd("usage: env\n", 2);
	// start of test (print strrerror)
	ft_putstr_fd("(test) strerrror : ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	// end of test
	return (1);
}

int	builtin_export(char **argv, t_env_info *env_info)
{
	t_env	*new;

	++argv;
	if (*argv)
		return (env_err());
	printenv(env_info->env);
	return (0);
}