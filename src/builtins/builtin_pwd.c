#include "builtins.h"
#include "libft.h"
#include "stdio.h"

#define	BUFFER_SIZE 1024

int	builtin_pwd(t_script *cur_cmd)
{
	char	*buf;

	buf = getcwd(NULL, BUFFER_SIZE);
	if (!buf)
		return (-1);
	// ft_putstr_fd(buf, cur_cmd->fd_out);
	// ft_putstr_fd("\n", cur_cmd->fd_out);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
