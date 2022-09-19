#include "minishell.h"
#include <string.h>
#include <errno.h>

void	ft_error(char *msg)
{
	char	*str_errno;

	str_errno = ft_strjoin(msg, strerror(errno));
	perror(str_errno);
	exit(EXIT_FAILURE);
}
