========readline===========
line = readline("minishell$ ")
line == 0
	exit(0)
*line == 0
	continue;

========parser===========
rvalue = parser(sh, line)
rvalue == 258 (syntax_err - quote)  [is_unvalid_quote()]
	continue;
rvalue == 258 (syntax_err - special character (>, <, |)) [tokenizer()]
	// token_clear();
	continue;
rvalue == 258 (syntax_err - grammar) [lexcial_analyze()]
	// token_clear();
	continue;

// ========termio===========
// sh->multi_cmd_flag = 0;
// if (sh->script->next)
// 	sh->multi_cmd_flag = 1;

========heredoc===========
rvalue(g_last_exit_value) = heredoc_readline(sh);

========execute===========
g_last_exit_value == 0
	rvalue(g_last_exit_value) = execute(sh);

// script_clear();

export a=123
echo $a
echo 123


