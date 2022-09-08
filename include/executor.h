#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>

# include "struct.h"
# include "env.h"
//# include "libft.h"

# define SHELL_NAME "minishell: "
# define FILE_NOT_FOUND 1
# define CMD_NOT_FOUND 127
# define CMD_NOT_FOUND_MSG "command not found"
# define FILE_NOT_FOUND_MSG "No such file or directory"

int	heredoc_execute(int herepipe[2], char *eof);

int	redirection(t_script *script);

t_bool	is_file_exists(char *file_name);

int		check_cmdpath(t_sh *sh, t_token *token);
//int		check_input_file(t_sh *sh, char *cmd, t_token *token);

char	**make_arguments(t_script *script);


#endif
