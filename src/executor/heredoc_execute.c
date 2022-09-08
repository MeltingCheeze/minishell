#include "executor.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
//#include "../../include/struct.h"
//#include "../../lib/libft/libft.h"

int g_is_heredoc;

static void	write_rl_in_pipe(int herepipe[2], char *eof)
{
	char 	*line;

	while (1)
	{
		line = readline(">");
		if (line == 0)
			break ;
		if (!ft_strcmp(line, eof) || *line == 0)
		{
			free(line);
			break ;
		}
		write(herepipe[1], line, ft_strlen(line));
		write(herepipe[1], "\n", 1);
		free(line);
	}
}

int	heredoc_execute(int herepipe[2], char *eof)
{
	int	pid;
	int	rvalue;

	rvalue = 0;
	pid = fork();
	if (!pid)
	{
		g_is_heredoc = 1;
		write_rl_in_pipe(herepipe, eof);
		exit(0);
	}
	wait(&rvalue);
	return (rvalue);
}
