#include <string.h>
#include <errno.h>
#include "libft.h"
#define SHELL_NAME "minishell: "

int	open_error(char *fname)
{
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(fname, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
