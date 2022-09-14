#include "env.h"
#include "libft.h"
#include "parser.h"

#define SHELL_NAME "minishell: "

int	export_err(char *content)
{
	// g_last_return_status = 1;
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
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
	char	**envp;
	int		rvalue;

	rvalue = 0;
	envp = argv;
	while (*(++envp))
	{
		ft_putendl_fd(*envp, 2);
		if (ft_strchr(*envp, '=') && !check_env_name(*envp))
		{
			new = envnew(*envp);
			envadd_back(&env_info->head, new);
			env_info->size++;
			ft_putnbr_fd(env_info->size, 2);
			ft_putchar_fd('\n', 2);
		}
		else if (rvalue == 0)
			rvalue = 1;
	}
	ft_free_pptr((void ***)&env_info->envp);
	free(argv);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (rvalue);
}