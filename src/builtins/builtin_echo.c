#include "libft.h"
#include "builtins.h"
#include <stdio.h>

int	builtin_echo(char **argv, t_script *cur_cmd)
{
	int	i;
	int	nl_flag;

	i = 1;
	nl_flag = 0;
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		nl_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], cur_cmd->fd_out);
		if (argv[i + 1])
			ft_putstr_fd(" ", cur_cmd->fd_out);
		i++;
	}
	if (nl_flag == 0)
		ft_putstr_fd("\n", cur_cmd->fd_out);
	return (0);
}
