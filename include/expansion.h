#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>
# include "struct.h"
# include "env.h"

int		expansion(t_sh *sh);
void	last_exit_value_expansion(char **dst);
void	param_expansion(t_env *env, char **dst, char *src, char *cur);

char	*attach_str(char *joined, char *expand);
char	*attach_param_prestr(char *joined, char *start, char *cur);
char	*attach_param_str(t_env *env, char *joined, char *cur);
int		count_key_len(char *str);

#endif
