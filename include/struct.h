#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include <termios.h>

int	g_last_exit_value;

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_builtin
{
	NONE,
	B_ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}				t_builtin;

typedef enum e_type
{
	CMD,
	WORD, //execve 의 argv
	FILENAME,
	PIPE,
	RD_IN,
	RD_OUT,
	RD_HEREDOC,
	RD_APPEND
}				t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
}				t_token;

typedef struct s_script
{
	t_token			*head; /* token devided by pipe */
	int				fd_in;
	int				fd_out;
	int				herecnt; // 마지막 heredoc 아니면 herepipe[0] 닫아버리기
	int				argc;
	struct s_script	*next;
}				t_script;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_env_info
{
	t_env	*head; // export 모든 정보  char **
	size_t	size;
	char	**envp; // 유효한 정보
}				t_env_info;

typedef struct s_sh
{
	t_script	*script;
	t_env_info	env_info;
	int			multi_cmd_flag;
	struct termios	echo_on;
	struct termios	echo_off;
}				t_sh;

#endif
