#include "minishell.h"
#include "executor.h"

int g_last_exit_value;

static int	minishell(t_sh *sh)
{
	char	*line;
	line = NULL;
	g_last_exit_value = 0;
	terminal_setting(sh);
	tcsetattr(STDOUT_FILENO, TCSANOW, &sh->echo_off);
	while (42)
	{
		line = readcmdline();
		if (line == NULL || !*line)
			continue ;
		if (parser(sh, line))
			continue ;

		/* builtin exit 함수 구현에 필요 */
		sh->multi_cmd_flag = 0;
		if (sh->script->next)
			sh->multi_cmd_flag = 1;

		/* heredoc read line */
		heredoc_readline(sh);
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
