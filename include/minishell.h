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
void	set_sigaction(struct sigaction *sa_ptr,
			void (*handler)(int, siginfo_t *, void *));
void	shell_sigaction(int signo, siginfo_t *info, void *context);

/* iostream */
char	*readcmdline(void);

/* utile */
void	ft_error(char *msg);
//void	ft_free_pptr(char *msg);

/* print */
void	tokenprint(t_token *token);
void	print_type(t_token *token);
void	scriptprint(t_script *script);

#endif
