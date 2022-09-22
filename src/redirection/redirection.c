/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 20:56:30 by hyko              #+#    #+#             */
/*   Updated: 2022/09/22 21:14:44 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "executor.h"

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
	int		rvalue;

	cur_token = cur_cmd->head;
	rvalue = 0;
	while (cur_token)
	{
		if (cur_token->type == RD_OUT)
		{
			rvalue = redir_out(cur_cmd, cur_token);
			if (rvalue != 0)
				return (rvalue);
		}
		else if (cur_token->type == RD_APPEND)
		{
			rvalue = redir_append(cur_cmd, cur_token);
			if (rvalue != 0)
				return (rvalue);
		}		
		else if (cur_token->type == RD_IN)
		{
			rvalue = redir_in(cur_cmd, cur_token);
			if (rvalue != 0)
				return (rvalue);
		}
		else if (cur_token->type == RD_HEREDOC)
		{
			rvalue = redir_heredoc(cur_cmd);
			if (rvalue != 0)
				return (rvalue);
		}
		cur_token = cur_token->next;
	}
	return (0);
}
