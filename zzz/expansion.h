#ifndef EXPANSION_H
# define EXPANSION_H

// # include <stdlib.h>
# include "struct.h"
# include "libft.h"

typedef struct s_expand
{
	char			*expand;
	int				loc_start;
	int				len;
	struct s_expand	*next;
}				t_expand;

t_expand	*expandnew(char *expand, int loc_start, int len);
void		expandadd_back(t_expand **expand, t_expand *new);
void		expandclear(t_expand **expand);

#endif
