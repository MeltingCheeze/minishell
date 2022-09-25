/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:42:23 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 18:10:52 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "env.h"
#include <errno.h>
#include <string.h>

static void	update_oldpwd(t_env_info *env_info)
{
	t_env	*oldpwd_env;
	char	*pwd;
	char	*env;

	oldpwd_env = find_env(env_info->head, "OLDPWD");
	if (oldpwd_env == NULL)
		return ;
	pwd = find_env_value(env_info->head, "PWD");
	env = ft_strjoin("OLDPWD=", pwd);
	export_new(env_info, env);
	free(env);
}

static void	update_pwd(t_sh *sh, t_env_info *env_info)
{
	t_env	*pwd_env;
	char	*env;

	pwd_env = find_env(env_info->head, "PWD");
	if (pwd_env == NULL)
		return ;
	env = ft_strjoin("PWD=", sh->cur_pwd);
	export_new(env_info, env);
	free(env);
}

int	builtin_cd(char **argv, t_env_info *env_info, t_sh *sh)
{
	char	*path;

	path = argv[1];
	if (!path || !ft_strcmp(path, "~") || !ft_strcmp(path, "~/"))
		path = find_env_value(env_info->head, "HOME");
	if (chdir(path) < 0)
	{
		ft_putstr_fd("mihishell: cd: ", 2);
		if (path)
		{
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		}
		else
			ft_putstr_fd(": HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	update_oldpwd(env_info);
	update_pwd(sh, env_info);
	ft_free_pptr((void ***)&env_info->envp);
	env_info->envp = make_envp(env_info->head, env_info->size);
	return (0);
}
