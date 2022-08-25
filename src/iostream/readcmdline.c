#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static int	is_valid_quotes(const char *line, int has)
{
	char	c;
	int		i;

	i = 0;
	while (*(line + i))
	{
		c = *(line + i);
		if (c == SINGLE && has == 0)
			has += SINGLE;
		else if (c == SINGLE && has == SINGLE)
			has -= SINGLE;
		else if (c == SINGLE && has == DOUBLE)
			;
		else if (c == DOUBLE && has == 0)
			has += DOUBLE;
		else if (c == DOUBLE && has == SINGLE)
			;
		else if (c == DOUBLE && has == DOUBLE)
			has -= DOUBLE;
		i++;
	}
	return (!has);
}

char	*readcmdline(void)
{
	char	*line;

	line = readline("minishell$");
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (*line)
		add_history(line);
	if (!is_valid_quotes(line, 0))
	{
		perror("minishell: syntax error with open quotes");
		free(line);
		return (NULL);
	}

	return (line);
}
