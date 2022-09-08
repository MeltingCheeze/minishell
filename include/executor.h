#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "struct.h"
# include "env.h"
//# include "libft.h"

int	heredoc_excute(int herepipe[2], char *eof, int fd_in); //test
int	heredoc(t_script *script);

#endif
