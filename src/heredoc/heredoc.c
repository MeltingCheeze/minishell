#include "executor.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

static void	expand_line(t_env *env, char **dst, char *src)
{
	char	*cur;
	int		len;

	if (*src == 0)
		return ;
	cur = src;
	while (*cur)
	{
		if (*cur == '$')
		{
			len = count_key_len(cur + 1);
			if (*(cur + 1) == '?')
				last_exit_value_expansion(dst);
			else if (len)
				param_expansion(env, dst, src, cur);
			return (expand_line(env, dst, cur + len + 1));
		}
		cur++;
	}
	*dst = attach_str(*dst, src);
}

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

// TODO : set_heredoc_signal() 로 핸들러 재설정 필요 SIGINT(ctrl + C) 동작 변경
void	heredoc_readline(t_sh *sh)
{
	int			statloc;
	char 		*line;
	char		*doc;
	char		*delimiter;
	t_script	*cur_cmd;
	t_token		*cur_token;

	cur_cmd = sh->script;
	if (fork() == 0)
	{
		signal(SIGINT, &signal_heredoc);
		while (cur_cmd)
		{
			cur_token = cur_cmd->head;
			while (cur_cmd->herecnt > 0)
			{
				doc = 0;
				while (cur_token) //find heredoc
				{
					if (cur_token->type == RD_HEREDOC)
						break ;
					cur_token = cur_token->next;
				}
				cur_token = cur_token->next;
				delimiter = cur_token->content;
				while (1) //read_line
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
				cur_cmd->herecnt--;
			}
			cur_cmd = cur_cmd->next;
		}
		if (doc)
			heredoc_write(sh, doc);
		exit(0);
	}
	wait(&statloc);
	g_last_exit_value = WEXITSTATUS(statloc);
}
