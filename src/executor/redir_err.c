// TODO : ERR (permission denied, file not found)
#include <unistd.h>
#include "libft.h"

static int	file_not_found_print(char *cmd, char *filename)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("No such file or directory", STDERR_FILENO);
	return (1);
}
