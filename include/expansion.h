#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

# include "struct.h"
# include "env.h"
# include "libft.h"

# define SHELL_NAME "minishell: "
# define FILE_NOT_FOUND 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_FOUND_MSG "command not found"
# define FILE_NOT_FOUND_MSG "No such file or directory"

t_bool	is_file_exists(char *file_name);

// int		expansion(t_sh *sh);
int		expansion(t_sh *sh, t_token *token); // test

void	parameter_expansion(t_sh *sh, t_token *token);
int		cmdpath_expansion(t_sh *sh, t_token *token);
int		input_file_checker(t_token *token);

#endif
