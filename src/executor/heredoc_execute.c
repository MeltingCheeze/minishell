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

static void	write_rl_in_pipe(t_env *env, int herepipe[2], char *eof)
{
	char	*line;

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
}

int	heredoc_execute(t_env *env, int herepipe[2], char *eof)
{
	int	pid;
	int	rvalue;

	rvalue = 0;
	pid = fork();
	if (!pid)
	{
		g_is_heredoc = 1;
		write_rl_in_pipe(env, herepipe, eof);
		exit(0);
	}
	wait(&rvalue);
	return (rvalue);
}
