#ifndef EXPANSION_H
# define EXPANSION_H

// # include <stdlib.h>
# include "struct.h"
# include "env.h"
# include "libft.h"

// int		expansion(t_sh *sh);
int		expansion(t_sh *sh, t_token *token); // test

void	parameter_expansion(t_sh *sh, t_token *token);

#endif
