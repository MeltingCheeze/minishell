#ifndef STRUCT_H
# define STRUCT_H

#include <stdio.h>
#include <stdlib.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			  t_bool;

typedef struct s_token
{
	char			*content;
	char 			type;
	struct s_token	*next;
}				t_token;

typedef struct s_script
{
	t_token			*cmd; /* token devided by pipe */
	int				fd_in;
	int				fd_out;
	struct s_script		*next;
}				t_script;

typedef struct s_env
{
	char			*key;
	char			**value;
	struct s_env	*next;
}				t_env;

typedef struct s_sh
{
	t_script	script;
	t_env		*env;
}				t_sh;


int    lexcial_analyze(t_token *line);
void    split_cmd(t_token *line);

#endif