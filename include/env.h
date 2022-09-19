#ifndef ENV_H
# define ENV_H

# include "struct.h"

int		env_init(t_env_info *env_info, char **envp);
int		env_terminate(t_env **env);
t_env	*envnew(char *s);
void	envadd_back(t_env **env, t_env *new);
void	envdel(t_env *env, char *key);

void	envprint(t_env *env);

char	**make_envp(t_env *env, int env_size);

char	*find_env_value(t_env *env, char *key);
t_env	*find_env(t_env *env, char *key); //없는 함수??

int		is_valid_env_first_name(char c);
int		is_valid_env_name(char c);

char	*getkey(char *s);

#endif
