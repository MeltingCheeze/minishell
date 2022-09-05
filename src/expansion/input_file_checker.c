#include "expansion.h"

static void	file_not_found_err(char *cmd, char *filename, int *exit_value)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(FILE_NOT_FOUND_MSG, STDERR_FILENO);
	*exit_value = FILE_NOT_FOUND;
}

int	input_file_checker(t_sh *sh, char *cmd, t_token *token)
{
	if (ft_strrchr(cmd, '/'))
		cmd = ft_strrchr(cmd, '/') + 1;
	if (!is_file_exists(token->content))
	{
		file_not_found_err(cmd, token->content, &sh->last_exit_value);
		return (1);
	}
	return (0);
}
