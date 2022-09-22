#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "struct.h"

# define UNCLOSED_QUOTE_MSG "syntax error unclosed quote"
# define SYNTAX_ERROR_MSG "syntax error near unexpected token `"

# define SEPS " \t\n"
# define DELIMS " \t\n><|\0"

char	set_quote(char old_quote, char new_quote);

int		tokenizer(t_token **token, char *line);

void	token_init(t_token *token);
t_token	*tokennew(char *content);
void	tokenadd_back(t_token **token, t_token *new);
void	tokenclear(t_token **token);

#endif