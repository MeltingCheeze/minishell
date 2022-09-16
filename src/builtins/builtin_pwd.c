#include "builtins.h"
#include "libft.h"
#include "stdio.h"

#define	BUFFER_SIZE 1024

int	builtin_pwd(t_script *cmd)
{
	char	*buf;

	buf = getcwd(NULL, BUFFER_SIZE);
	ft_putstr_fd(buf, cmd->fd_out);
	ft_putstr_fd("\n", cmd->fd_out);
	free(buf);
	return (0);
}
