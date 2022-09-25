/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:56:30 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 14:32:30 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	redir_out(t_script *cur_cmd, t_token *cur_token)
{
	if (cur_cmd->fd_out != 1)
		close(cur_cmd->fd_out);
	cur_cmd->fd_out = open(cur_token->next->content,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cur_cmd->fd_out < 0)
		return (open_error(cur_token->next->content));
	return (0);
}

static int	redir_append(t_script *cur_cmd, t_token *cur_token)
{
	if (cur_cmd->fd_out != 1)
		close(cur_cmd->fd_out);
	cur_cmd->fd_out = open(cur_token->next->content,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cur_cmd->fd_out < 0)
		return (open_error(cur_token->next->content));
	return (0);
}

static int	redir_in(t_script *cur_cmd, t_token *cur_token)
{
	if (cur_cmd->fd_in != 0)
		close(cur_cmd->fd_in);
	cur_cmd->fd_in = open(cur_token->next->content, O_RDONLY, 0644);
	if (cur_cmd->fd_in < 0)
		return (open_error(cur_token->next->content));
	return (0);
}

static int	redir_heredoc(t_script *cur_cmd)
{
	if (cur_cmd->fd_in != 0)
		close(cur_cmd->fd_in);
	cur_cmd->fd_in = open("/tmp/msh_heredoc", O_RDONLY, 0644);
	if (cur_cmd->fd_in < 0)
		return (open_error("heredoc"));
	return (0);
}

int	redirection(t_script *cur_cmd)
{
	t_token	*cur_token;
	int		result;

	cur_token = cur_cmd->head;
	result = 0;
	while (cur_token && result == 0)
	{
		if (cur_token->type == RD_OUT)
			result = redir_out(cur_cmd, cur_token);
		else if (cur_token->type == RD_APPEND)
			result = redir_append(cur_cmd, cur_token);
		else if (cur_token->type == RD_IN)
			result = redir_in(cur_cmd, cur_token);
		else if (cur_token->type == RD_HEREDOC)
			result = redir_heredoc(cur_cmd);
		cur_token = cur_token->next;
	}
	return (result);
}
