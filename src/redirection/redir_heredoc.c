/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:12:49 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 20:33:08 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"
#include "redirection.h"

static void	heredoc_write(t_sh *sh, char *doc)
{
	char	*expanded_str;
	int		fd;

	expanded_str = 0;
	fd = open("/tmp/msh_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (ft_strchr(doc, '$') == 0)
		ft_putstr_fd(doc, fd);
	else
	{
		expand_line(sh->env_info.head, &expanded_str, doc);
		ft_putstr_fd(expanded_str, fd);
		free(expanded_str);
	}
	close(fd);
}

static t_token	*find_heredoc(t_token *token)
{
	while (token)
	{
		if (token->type == RD_HEREDOC)
			break ;
		token = token->next;
	}
	token = token->next;
	return (token);
}

static char	*read_line(char *delimiter)
{
	char	*line;
	char	*doc;

	doc = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		if (*line)
		{
			doc = attach_str(doc, line);
			free(line);
		}
		doc = attach_str(doc, "\n");
	}
	return (doc);
}

static char	*do_heredoc(t_script *cur_cmd, char *delimiter)
{
	char	*doc;
	t_token	*cur_token;

	doc = 0;
	cur_token = cur_cmd->head;
	while (cur_cmd->herecnt > 0)
	{
		doc = 0;
		cur_token = find_heredoc(cur_token);
		delimiter = cur_token->content;
		doc = read_line(delimiter);
		cur_cmd->herecnt--;
	}
	return (doc);
}

void	heredoc_read_line(t_sh *sh)
{
	int			statloc;
	char		*doc;
	char		*delimiter;
	t_script	*cur_cmd;

	cur_cmd = sh->script;
	delimiter = 0;
	signal(SIGINT, SIG_IGN);
	if (fork() == 0)
	{
		signal(SIGINT, &signal_heredoc);
		while (cur_cmd)
		{
			doc = do_heredoc(cur_cmd, delimiter);
			cur_cmd = cur_cmd->next;
		}
		if (doc)
			heredoc_write(sh, doc);
		exit(0);
	}
	wait(&statloc);
	signal(SIGINT, signal_readline);
	g_last_exit_value = WEXITSTATUS(statloc);
}
