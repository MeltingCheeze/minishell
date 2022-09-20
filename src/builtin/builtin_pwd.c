#include "builtin.h"
#include "libft.h"
#include <stdio.h>
#include <errno.h>

#define	BUFFER_SIZE 1024

int	builtin_pwd(t_script *cur_cmd)
{
	char	*buf;

	buf = getcwd(NULL, BUFFER_SIZE);
	if (!buf)
		return (errno);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
