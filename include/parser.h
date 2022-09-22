#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include "struct.h"

int		parser(t_sh *sh, char *line);

int		lexcial_analyze(t_token *token);

void	tokens_to_cmds(t_sh *sh, t_token *token);

void	remove_quote(t_script *script);

#endif
