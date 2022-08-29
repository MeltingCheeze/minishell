typedef struct s_token
{
	char			*content;
	char 			type;
	struct s_token	*next;
}			   t_token;

typedef struct s_cmd_list
{
	t_token			*cmd; /* token devided by pipe */
	int				fd_in;
	int				fd_out;
	s_cmd_list		*next;
}			   t_cmd_list;

