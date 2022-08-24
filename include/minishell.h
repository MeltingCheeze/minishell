#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# include "libft.h"
# include "struct.h"
# include "parse.h"
# include "env.h"

/* metacharacters */
# define PIPE "|"
# define LESS "<"
# define GRATE ">"
# define DLESS "<<"
# define DGREAT ">>"
# define LESSAND "<&"
# define GREATAND ">&"
# define QMARK '?'
# define DOLLAR '$'
# define SPACE ' '
# define SEMICOLON ';'
# define SINGLE '\''
# define DOUBLE '"'
# define BSLASH '\\'

//# define TAKE "%d %d has taken a fork\n"
//# define EAT "\033[0;33m%d %d is eating\n\033[0m"
//# define SLEEP "\033[0;35m%d %d is sleeping\n\033[0m"
//# define THINK "\033[0;32m%d %d is thinking\n\033[0m"
//# define DEAD "\033[0;31m%d %d died\n\033[0m"

//# define DOUBLE '"'

/* signal */
void	set_sigaction(struct sigaction *sa_ptr,
						void (*handler)(int, siginfo_t *, void *));
void	shell_sigaction(int signo, siginfo_t *info, void *context);

/* iostream */
char	*readcmdline(void);
char	check_quote(const char *line, int i);

/* utile */
void	ft_error(char *msg);
//void	ft_free_pptr(char *msg);

#endif
