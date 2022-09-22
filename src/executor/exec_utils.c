/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:46:40 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 00:29:07 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <unistd.h>
#include <libft.h>
#include "utils.h"

int	is_path(char *s)
{
	if (ft_strchr(s, '/'))
		return (1);
	return (0);
}

static char	**find_paths(t_env *env)
{
	char	*value;
	char	**paths;

	value = find_env_value(env, "PATH");
	if (value == NULL)
		value = getenv("PATH");
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
	if (!token)
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
	free(token->content);
	token->content = cmd_path;
	return (cmd_path);
}

char	**make_arguments(t_script *script)
{
	char	**result;
	t_token	*token;
	int		i;

	result = (char **)malloc(sizeof(char *) * (script->argc + 1));
	i = 0;
	token = script->head;
	while ((i < script->argc) && (token))
	{
		while (token && (token->type > WORD))
			token = token->next;
		if (*token->content)
			result[i++] = token->content;
		token = token->next;
	}
	result[i] = 0;
	return (result);
}
