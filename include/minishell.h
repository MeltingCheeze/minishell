#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>

# include "libft.h"
# include "struct.h"
# include "parser.h"
# include "env.h"

/* signal */
void	set_signal(void);
void	set_heredoc_signal(void);

/* iostream */
char	*readcmdline(void);

/* utils */
void	ft_error(char *msg);
// t_bool	is_file_exists(char *file_name);
//void	ft_free_pptr(char *msg);

/* print */
void	wordsprint(char	**words);
void	tokenprint(t_token *token);
void	print_type(t_token *token);
void	scriptprint(t_script *script);

/* execute -> 헤더 쪼개기 */
int	execute(t_sh *sh);


/* signal */
void	terminal_setting(t_sh *sh);
void	signal_readline(int	signo);
void	signal_execute(int	signo);
void	signal_heredoc(int	signo);

/* redirection ->헤더 분리 */
void	heredoc_readline(t_sh *sh);
int	redirection(t_script *cur_cmd);
void	heredoc_readline(t_sh *sh);
int	open_error(char *fname);

#endif
