#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

char	*readcmdline(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}
