#include "env.h"
#include "libft.h"

int	is_valid_env_name(char c)
{
	return (ft_isdigit(c) || ft_isalpha(c) || (c == '_'));
}
