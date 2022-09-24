/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:55:06 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 13:15:14 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "msh_struct.h"

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
