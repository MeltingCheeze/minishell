#ifndef BUILTINS_H
# define BUILTINS_H

# include "struct.h"

int	builtin_export(char **argv, t_env_info *env_info);

int	builtin_env(char **argv, t_env_info *env_info);

#endif
