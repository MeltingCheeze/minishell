#include "expansion.h"


static t_bool	is_file_exists(char *file_name)
{
	struct stat	buf;

	return (stat(file_name, &buf) == 0);
}

int	input_file_checker(t_token *token)
{
	if (!is_file_exists(token->content))
		return (1);
	return (0);
}
