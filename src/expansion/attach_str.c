#include <stdlib.h>
#include "libft.h"

char	*attach_str(char *joined, char *expand)
{
	char	*result;

	result = ft_strjoin(joined, expand);
	free(joined);
	return (result);
}