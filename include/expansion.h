#ifndef EXPANSION_H
# define EXPANSION_H

# include <stdlib.h>

# include "struct.h"
# include "env.h"
# include "libft.h"

int		expansion(t_sh *sh);

char	*attach_str(char *joined, char *expand);
char	*do_expand(t_env *env, char *joined, char **start, char **cur);
void	parameter_expansion(t_sh *sh, t_token *token);

#endif
