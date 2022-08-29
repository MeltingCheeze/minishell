#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

# define SEPS " ><|"

//int		parse(t_sh *sh, char *line);
int		parse(t_script *script, char *line);

t_token	*tokenizer(char *line);

void	token_init(t_token *token);
t_token	*tokennew(char *content);
void	tokenadd_back(t_token **token, t_token *new);
void	tokenprint(t_token **token);
void	tokenclear(t_token **token);

#endif
