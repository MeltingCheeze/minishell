#include "env.h"
#include "libft.h"
#include "parser.h"
#include "builtins.h"

#define SHELL_NAME "minishell: "

static int	export_err(char *content)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	return (1);
}

static int	check_env_name(char *s)
{
	char	*cur;

	cur = s;
	while (*cur != '=' && is_valid_env_name(*cur))
		cur++;
	if (*cur && *cur != '=')
		return (1);
	return (0);
}

static void	export_env(t_env_info *env_info, char **envp)
{
	t_env	*new;

	if (**envp == '_' && *(*envp + 1) == '\0')
		return ; // 이거 어떻게 할지 모르겠음
	new = envnew(*envp);
	envadd_back(&env_info->head, new);
	env_info->size++;
}

int	builtin_export(char **argv, t_env_info *env_info)
{
	char	**envp;
	int		rvalue;

	rvalue = 0;
	envp = argv;
	if (!*(envp + 1))
	{
		no_argv_print(env_info);
		return (rvalue);
	}
	while (*(++envp))
	{
		if (is_valid_env_first_name(**envp) && !check_env_name(*envp))
			export_new(env_info, *envp);
		else
			rvalue = export_err(*envp);
	}
	ft_free_pptr((void ***)&env_info->envp);
	free(argv);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (rvalue);
}
