//int	expand_tokens()
//{
	//  [todo] = += 대입연산
	//  3. parameter and variable expansion [$ 매개변수 확장]
	//  5. command substitution [echo $(date +%D)]
	//  6. word splitting
	//  7. filename expansion
//}

void	do_line(t_token **token)
{
	t_token	*cur;
	char	*new;

	cur = *token;
	while (cur)
	{
		new = 0;
		if ((cur->type == 'w') || (cur->type == 'c')) // !(cur->type & heardoc)   cur->type == CMD
		{
			new = cur->content;
			while (new)
			{
				new = ft_strchr(cur->content, '$');
				parameter_expansion();
			}
			if  (file_expansion()) // && file
				return (1);
		}
		cur = cur->next;
	}
}

int	expansion(t_sh *sh)
{
	t_script	*cmd;
	t_token		*t;

	cmd = sh->script;
	while (cmd)
	{
		t = cmd->cmd;
		expand_tokens();
		cmd = cmd->next;
	}

}