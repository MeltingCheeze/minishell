#include "env.h"
#include "libft.h"
#include "parser.h"
#include "builtins.h"

#define SHELL_NAME "minishell: "

static int	unset_err(char *content)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd("not a valid identifier", 2);
	return (1);
}

static int	check_env_name(char *s)
{
	char	*cur;

	cur = s;
	while (is_valid_env_name(*cur))
		cur++;
	if (*cur)
		return (1);
	return (0);
}

static void	unset_env(t_env_info *env_info, char **envp)
{
	int		len;
	char	*key;
	t_env	*env;
	t_env	*next;

	if (**envp == '_' && *(*envp + 1) == '\0')
		return ; // 이거 어떻게 할지 모르겠음
	len = keylen(*envp);
	key = ft_substr(*envp, 0, len);
	envdel(env_info->head, key);
	free(key);
}

int	builtin_unset(char **argv, t_env_info *env_info)
{
	char	**envp;
	int		rvalue;

	rvalue = 0;
	envp = argv;
	if (!*(envp + 1))
		return (rvalue);
	while (*(++envp))
	{
		if (!**envp
			|| (is_valid_env_first_name(**envp) && !check_env_name(*envp)))
			unset_env(env_info, envp);
		else
			rvalue = unset_err(*envp);
	}
	ft_free_pptr((void ***)&env_info->envp);
	free(argv);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (rvalue);
}
