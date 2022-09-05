#include "env.h"

int	keylen(char *s)
{
	int	len;

	len = 0;
	while (is_valid_env_name(*(s + len)) && (*(s + len) != '\0'))
		len++;
	return (len);
}
