#include "builtin.h"
#include "libft.h"
#include "env.h"
#include <stdio.h>

static void	update_oldpwd(t_env_info *env_info)
{
	char	*old_pwd;
	char	*pwd;
	char	*env;

	old_pwd = find_env_value(env_info->head, "OLDPWD");
	if (old_pwd == NULL)
		return ;
	pwd = find_env_value(env_info->head, "PWD");
	if (pwd)
		env = ft_strjoin("OLDPWD=", pwd);
	else
		env = ft_strdup("OLDPWD=");
	export_new(env_info, env);
	free(env);
}

static void	update_pwd(t_env_info *env_info)
{
	char	*pwd;
	char	*env;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		// posix error
		return ;
	}
	env = ft_strjoin("PWD=", pwd);
	free(pwd);
	export_new(env_info, env);
	free(env);
}

int	builtin_cd(char **argv, t_env_info *env_info)
{
	char	*path;
	int		rvalue;

	rvalue = 0;
	path = argv[1];
	if (!path || !ft_strcmp(path, "~") || !ft_strcmp(path, "~/")) // $HOME
		path = find_env_value(env_info->head, "HOME");
		// path = getenv("HOME");
	rvalue = chdir(path);
	if (rvalue < 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		return (rvalue); // 이거 왜 errno 가 아닐까 -> EXIT_FAILURE ??
	}
	update_oldpwd(env_info);
	update_pwd(env_info);
	ft_free_pptr((void ***)&env_info->envp);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (0);
}
