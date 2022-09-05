#include "expansion.h"

int	input_file_checker(t_token *token)
{
	if (!is_file_exists(token->content))
		return (1);
	return (0);
}
