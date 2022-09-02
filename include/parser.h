#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include "struct.h"

# define SPACE ' '
# define SINGLE '\''
# define DOUBLE '"'
# define SEPS " ><|"

int		parser(t_sh *sh, char *line);

t_token	*tokenizer(char *line);

void	token_init(t_token *token);
t_token	*tokennew(char *content);
void	tokenadd_back(t_token **token, t_token *new);
void	tokenclear(t_token **token);

int		lexcial_analyze(t_token *line);

#endif
