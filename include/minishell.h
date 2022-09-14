#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>

# include "libft.h"
# include "struct.h"
# include "signal.h"
# include "parser.h"
# include "env.h"

/* signal */
void	set_signal(void);
void	signal_handler(int signo);

/* iostream */
char	*readcmdline(void);

/* utile */
void	ft_error(char *msg);
// t_bool	is_file_exists(char *file_name);
//void	ft_free_pptr(char *msg);

/* print */
void	wordsprint(char	**words);
void	envprint(t_env *env);
void	tokenprint(t_token *token);
void	print_type(t_token *token);
void	scriptprint(t_script *script);

/* execute -> 헤더 쪼개기 */
int	execute(t_sh *sh);
int		redirection(t_script *cur_cmd);


#endif
