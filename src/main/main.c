#include "minishell.h"
#include "executor.h"

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
		/* heredoc read line */
		heredoc_read_line(sh);
		execute(sh);
		free(line);
		unlink("tmp");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	(void)argc;
	(void)argv;
	env_init(&sh.env_info, envp);
	minishell(&sh);
	env_terminate(&sh.env_info.head);
}
