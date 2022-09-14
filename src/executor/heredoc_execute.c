#include "executor.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>

int	g_is_heredoc;

// static char	*expand_line(t_env *env, char *line)
// {
// 	char	*start;
// 	char	*cur;
// 	char	*result;

// 	result = 0;
// 	cur = line;
// 	start = line;
// 	cur = ft_strchr(line, '$');
// 	if (!cur)
// 		return (line);
// 	while (cur && is_valid_env_name(*(cur + 1)))
// 	{
// 		result = do_expand(env, result, &start, &cur);
// 		cur = ft_strchr(cur, '$');
// 	}
// 	if (start)
// 		result = attach_str(result, start);
// 	free(line);
// 	return (result);
// }

// int	heredoc_execute(t_env *env, int fd[2], int herecnt, char *eof)
// {
// 	int		pid;
// 	int		rvalue;
// 	char	*line;
// 	char	*result;

// 	rvalue = 0;
// 	pid = fork();
// 	if (!pid)
// 	{
// 		g_is_heredoc = 1;
// 		result = 0;
// 		while (1)
// 		{
// 			line = readline(">");
// 			if (line == 0)
// 				break ;
// 			if (!ft_strcmp(line, eof))
// 			{
// 				free(line);
// 				break ;
// 			}
// 			if (*line)
// 			{
// 				line = expand_line(env, line);
// 				result = attach_str(result, line);
// 			}
// 			result = attach_str(result, "\n");
// 			free(line);
// 		}
// 		if (!herecnt)
// 			write(fd[1], result, ft_strlen(result));
// 		free(result);
// 		g_is_heredoc = 0;
// 		exit(0);
// 	}
// 	wait(&rvalue);
// 	return (rvalue);
// }

int	heredoc_read_line(t_script *first_cmd)
{
	char *line;
	char *doc;
	char *delimiter;
	int	fd;
	t_script	*cur_cmd;
	t_token	*cur_token;

	cur_cmd = first_cmd;
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
				if (!ft_strcmp(line, delimiter))
				{
					free(line);
					break ;
				}
				if (*line)
				{
					doc = ft_strjoin(doc, line);
					doc = ft_strjoin(doc, "\n");
				}
			}
			fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
			ft_putstr_fd(doc, fd);
			close(fd);
			cur_cmd->herecnt--;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}
