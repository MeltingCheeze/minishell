#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

int		builtin_export(char **argv, t_env_info *env_info);
void	no_argv_print(t_env_info *env_info);

int		builtin_env(char **argv, t_env_info *env_info);

int		builtin_unset(char **argv, t_env_info *env_info);

int		builtin_echo(char **argv, t_script *cmd);

#endif
