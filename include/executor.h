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
# define READ 0
# define WRITE 1

int	redirection(t_script *cur_cmd);
// int	redirection(t_env *env, t_script *script);
int	open_error(char *fname);
// int	heredoc_execute(t_env *env, int fd[2], int herecnt, char *eof);
int		heredoc_read_line(t_script *first_cmd);

t_bool		is_file_exists(char *file_name); // utiles
t_builtin	is_builtins(t_token *token);

int		is_path(char *s);

char	*cmd_to_path(t_sh *sh, t_token *token);

char	**make_arguments(t_script *script);

void	execute_error(char *cmd);

#endif
