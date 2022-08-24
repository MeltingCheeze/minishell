#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_type
{
	Script,
	Pipeline,
	Word, /*  basic unit */
	ParameterExpansion,
	CommandExpansion
}			t_type;

typedef struct s_token
{
	char			*word;
	int				n;
	char			sep;
	struct s_token	*next;
}				t_token;

/**
 * When type is "ParameterExpansion", (char *)word
 * When type is "CommandExpansion", (t_script *)word
 */
typedef struct s_expan
{
	t_type		type;
	void		*word;
	int			loc_start;
	int			loc_end;
}				t_expan;

typedef struct s_value
{
	t_type			type;
	char			*text;
	char			*opt;
	char			*fname;
	t_expan			*expan;
	struct s_value	*next;
}				t_value;

typedef struct s_cmd
{
	t_type			type;
	char			*name;
	t_value			value;
	struct s_cmd	*next;
	//t_value			prefix;
	//t_value			suffix;
	//int		fd_in;
	//int		fd_out;
}				t_cmd;

typedef struct s_script
{
	t_type	type;
	t_cmd	cmd;
}			t_script;

typedef struct s_env
{
	char 			*key;
	char 			**value;
	struct s_env	*next;
}				t_env;

typedef struct s_sh
{
	t_script	script;
	t_env		*env;
}				t_sh;

#endif
