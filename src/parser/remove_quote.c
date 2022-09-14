#include "parser.h"
#include "libft.h" // 나중에 고치기

static void	rm_token_quote(char *dest, char *src, char quote)
{
	while (*src)
	{
		if (*src == '\'' || *src == '"')
		{
			quote = *src;
			src++;
			while (*src != quote)
			{
				*dest = *src;
				src++;
				dest++;
			}
			quote = 0;
			src++;
		}
		else
		{
			*dest = *src;
			src++;
			dest++;
		}
	}
	*dest = *src;
}


static void	rm_cmd_quote(t_token *cmd)
{
	while (cmd)
	{
		rm_token_quote(cmd->content, cmd->content, 0);
		cmd = cmd->next;
	}
}

void	remove_quote(t_script *script)
{
	while (script)
	{
		rm_cmd_quote(script->head);
		script = script->next;
	}
}
