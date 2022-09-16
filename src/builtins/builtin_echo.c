#include "libft.h"
#include "builtins.h"

int	builtin_echo(char **argv, t_script *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argv[i] && ft_strcmp(argv[i], "-n") == 0)
	{
		flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], cmd->fd_out);
		if (argv[i + 1])
			ft_putstr_fd(" ", cmd->fd_out);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}
