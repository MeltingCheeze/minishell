#include "minishell.h"

static int	minishell(t_sh *sh)
{
	char				*line;
	struct sigaction	sa;

	set_sigaction(&sa, shell_sigaction);
	line = NULL;
	while (42)
	{
		line = readcmdline();
		if (line == NULL || !*line)
			continue ;
		parse(&sh->script, line);
		//exec();
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
