#include "executor.h"
#include "expansion.h"
#include <stdio.h>
#include <readline/readline.h>

int	g_is_heredoc;

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


int	heredoc_execute(t_env *env, int herepipe[2], char *eof)
{
	char	*line;

	g_is_heredoc = 1;
	while (1)
	{
		line = readline(">");
		if (line == 0)
			break ;
		if (!ft_strcmp(line, eof))
		{
			free(line);
			break ;
		}
		if (*line)
		{
			line = expand_line(env, line);
			write(herepipe[1], line, ft_strlen(line));
		}
		write(herepipe[1], "\n", 1);
		free(line);
	}
	return (0);
}
