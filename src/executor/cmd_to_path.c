#include "executor.h"
#include <unistd.h>
#include <libft.h>

static char	**find_paths(t_env *env)
{
	char	*value;
	char	**paths;

	// value = getenv("PATH");
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

char	*cmd_to_path(t_sh *sh, t_token *token)
{
	char	**paths;
	char	*cmd_path;

	while (token && (token->type != CMD))
		token = token->next;
	if (!token) // ls | << eof 헸을때 세그폴트 떠서 일단 막아놨어! 문제 있음 수정해줘~~
		return (NULL);
	if (*token->content == '\0')
		return (NULL);
	cmd_path = token->content;
	if (is_path(cmd_path) || !ft_strcmp(cmd_path, "."))
		return (token->content);
	paths = find_paths(sh->env_info.head);
	cmd_path = match_path(paths, token->content, ft_strlen(token->content));
	ft_free_pptr((void ***)&paths);
	if (!cmd_path)
		return (token->content);
	free(token->content); // 이거 
	token->content = cmd_path; // 랑 이거 변경해야하나 말아도 되나 고민중
	return (cmd_path);
}
