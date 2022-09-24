/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaejkim <chaejkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:54:57 by hyko              #+#    #+#             */
/*   Updated: 2022/09/24 13:15:14 by chaejkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>

# include "libft.h"
# include "msh_struct.h"
# include "parser.h"
# include "env.h"

/* signal */
void	set_signal(void);
void	set_heredoc_signal(void);

/* iostream */
char	*readcmdline(void);

/* utils */
void	ft_error(char *msg);

/* print */
void	wordsprint(char	**words);
void	tokenprint(t_token *token);
void	print_type(t_token *token);
void	scriptprint(t_script *script);

/* signal */
void	terminal_setting(t_sh *sh);
void	signal_readline(int signo);
void	signal_execute(int signo);
void	signal_heredoc(int signo);

#endif
