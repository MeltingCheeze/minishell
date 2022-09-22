#include "executor.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>
#include "minishell.h"

static char	*expand_line(t_env *env, char *line)
{
	char	*start;
	char	*cur;
	char	*result;

	result = 0;
	cur = line;
	start = line;
	cur = ft_strchr(line, '$');
	if (!cur)
		return (line);
	while (cur && is_valid_env_name(*(cur + 1)))
	{
		result = do_expand(env, result, &start, &cur);
		cur = ft_strchr(cur, '$');
	}
	if (start)
		result = attach_str(result, start);
	free(line);
	return (result);
}

static void	heredoc_write(t_sh *sh, char *doc)
{
	int	fd;

	doc = expand_line(sh->env_info.head, doc);
	fd = open("/tmp/msh_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	// if (fd < 0)
	// {
	// 	open_error("heredoc");
	// 	return ;
	// }
	// if (!doc)
	// {
	// 	ft_putstr_fd("!doc\n", 2);
	// 	return ;
	// }
	ft_putstr_fd(doc, fd);
	free(doc);
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
