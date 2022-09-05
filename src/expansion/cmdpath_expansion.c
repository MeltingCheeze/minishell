#include "expansion.h"

static char	**find_paths(t_env *env)
{
	char	*value;
	char	**paths;

	value = find_env_value(env, "PATH");
	paths = ft_split(value, ':');
	return (paths);
}

static char	*match_path(char **paths, char *cmd, size_t cmd_len)
{
	char	*cmd_path;
	int		i;
	size_t	size;
	size_t	path_len;

	i = -1;
	while (paths[++i])
	{
		path_len = ft_strlen(paths[i]);
		size = path_len + cmd_len + 2;
		cmd_path = (char *)ft_calloc(size, sizeof(char));
		ft_strlcat(cmd_path, paths[i], size);
		cmd_path[path_len] = '/';
		ft_strlcat(cmd_path, cmd, size);
		cmd_path[size - 1] = 0;
		if (is_file_exists(cmd_path))
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

static void	cmd_not_found_err(char *cmd, int *exit_value)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(CMD_NOT_FOUND_MSG, STDERR_FILENO);
	*exit_value = CMD_NOT_FOUND;
}

int	cmdpath_expansion(t_sh *sh, t_token *token)
{
	char	**paths;
	char	*cmd_path;

	paths = find_paths(sh->env);
	cmd_path = match_path(paths, token->content, ft_strlen(token->content));
	ft_free_pptr((void ***)&paths);
	if (!cmd_path)
	{
		cmd_not_found_err(token->content, &sh->last_exit_value);
		return (1);
	}
	free(token->content);
	token->content = cmd_path;
	return (0);
}