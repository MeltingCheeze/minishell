#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include "struct.h"

# define UNCLOSED_QUOTE_MSG "syntax error unclosed quote"
# define SYNTAX_ERROR_MSG "syntax error near unexpected token `"

# define SEPS " \t\n"
# define DELIMS " \t\n><|"

int		parser(t_sh *sh, char *line);

t_token	*tokenizer(char *line);

void	token_init(t_token *token);
t_token	*tokennew(char *content);
void	tokenadd_back(t_token **token, t_token *new);
void	tokenclear(t_token **token);

int		lexcial_analyze(t_token *token);

void	tokens_to_cmds(t_sh *sh, t_token *token);

void	remove_quote(t_script *script);

#endif
