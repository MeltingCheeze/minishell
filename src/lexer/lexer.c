/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:33:15 by hyko              #+#    #+#             */
/*   Updated: 2022/09/23 16:43:25 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static void	syntax_err(t_token *token)
{
	if (token == NULL || (token && *token->content == 0))
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token `newline'\n", 2);
		return ;
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd("'\n", 2);
	}
	g_last_exit_value = 258;
}

static void	check_type(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		if (ft_strcmp(curr->content, "|") == 0)
			curr->type = PIPE;
		else if (ft_strcmp(curr->content, "<") == 0)
			curr->type = RD_IN;
		else if (ft_strcmp(curr->content, ">") == 0)
			curr->type = RD_OUT;
		else if (ft_strcmp(curr->content, "<<") == 0)
			curr->type = RD_HEREDOC;
		else if (ft_strcmp(curr->content, ">>") == 0)
			curr->type = RD_APPEND;
		else
			curr->type = WORD;
		curr = curr->next;
	}
	while (token)
	{
		if (token->type > 3 && token->next && token->next->type == WORD)
			token->next->type = FILENAME;
		token = token->next;
	}
}

static void	check_cmd(t_token *token)
{
	while (token && token->type != WORD)
		token = token->next;
	if (token == NULL)
		return ;
	token->type = CMD;
	while (token)
	{
		if (token->type == PIPE)
		{
			while (token->type != WORD)
			{
				if (token->next)
					token = token->next;
				else
					return ;
			}
			token->type = CMD;
		}
		token = token->next;
	}
	return ;
}

static int	check_grammar(t_token *token)
{
	t_token	*next;

	if (token->type == PIPE)
	{
		syntax_err(token);
		return (1);
	}
	while (token)
	{
		next = token->next;
		if (token->type == PIPE && next && next->type == PIPE)
			break ;
		else if (token->type > 3 && next && next->type != FILENAME)
			break ;
		if (!next && (token->type >= RD_IN || token->type == PIPE))
			break ;
		token = token->next;
	}
	if (token)
	{
		syntax_err(token->next);
		return (1);
	}
	return (0);
}

int	lexcial_analyze(t_token *token)
{
	check_type(token);
	check_cmd(token);
	if (check_grammar(token) != 0)
		return (1);
	return (0);
}
