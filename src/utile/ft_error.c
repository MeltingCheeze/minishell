#include "minishell.h"
#include <string.h>
#include <errno.h>

void	syntax_err(char *s, int flag)
{
	fd_putstr_fd("minishell: syntax error near unexpected token ", 2);
	ft_putendl_fd(s, 2);
	free(msg);
	flag == 0
	// 
	flag == 1
	free(token)
	2
	free(token)
	free(script)

}

void	ft_error(char *msg)
{
	char	*str_errno;

	str_errno = ft_strjoin(msg, strerror(errno));
	perror(str_errno);
	exit(EXIT_FAILURE);
}
