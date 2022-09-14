#include "libft.h"

int	is_path(char *s)
{
	if (ft_strchr(s, '/'))
		return (1);
	return (0);
}


