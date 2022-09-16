#include "builtins.h"
#include "libft.h"
#include "stdio.h"

#define	BUFFER_SIZE 1024

int	builtin_pwd()
{
	char	*buf;

	buf = getcwd(NULL, BUFFER_SIZE);
	if (!buf)
		return (-1);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
