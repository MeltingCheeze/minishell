#include "env.h"
#include "libft.h"
#include <errno.h> // test
#include <string.h> // test

#define SHELL_NAME "minishell: "

int	export_err(char *content)
{
	// g_last_return_status = 1;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	// start of test (print strrerror)
	ft_putstr_fd("(test) strerrror : ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	// end of test
	return (1);
}

int	check_env_name(char *s)
{
	char	*cur;

	cur = s;
	while (*cur != '=' && is_valid_env_name(*cur))
		cur++;
	if (*cur != '=')
		return(export_err(s));
	return (0);
}

int	builtin_export(char **argv, t_env_info *env_info)
{
	t_env	*new;

	while (*(++argv))
	{
		ft_putendl_fd(*argv, 2);
		if (ft_strchr(*argv, '='))
		{
			if (check_env_name(*argv))
				return (1);
			new = envnew(*argv);
			envadd_back(&env_info->head, new);
			env_info->size++;
		}
	}
	ft_free_pptr((void ***)env_info->envp);
	ft_free_pptr((void ***)argv);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (0);
}