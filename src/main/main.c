#include "minishell.h"

int g_is_heredoc;

static int	minishell(t_sh *sh)
{
	char				*line;

	set_signal();
	line = NULL;
	g_is_heredoc = 0;
	while (42)
	{
		line = readcmdline();
		if (line == NULL || !*line)
			continue ;
		if (parser(sh, line))
			continue ;
		execute(sh);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	(void)argc;
	(void)argv;
	env_init(&sh.env, envp);
	minishell(&sh);
	env_terminate(&sh.env);
}
