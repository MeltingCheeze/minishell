#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "struct.h"

int		env_init(t_env **env, char **envp);
int		env_terminate(t_env **env);
t_env	*envnew(char *key, char *value);
void	envadd_back(t_env **env, t_env *new);
char	*find_env_value(t_env *env, char *key);

int		is_valid_env_name(char c);

#endif
