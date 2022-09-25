/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:54:59 by hyko              #+#    #+#             */
/*   Updated: 2022/09/25 16:52:08 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include "msh_struct.h"

int		parser(t_sh *sh, char *line);

int		lexcial_analyze(t_token *token);

void	add_script(t_script **script, t_token *head, int argc, int herecnt);

void	tokens_to_cmds(t_sh *sh, t_token *token);

#endif
