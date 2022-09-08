#include "executor.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
//#include "../../include/struct.h"
//#include "../../lib/libft/libft.h"

int g_is_heredoc;

static void	write_rl_in_pipe(int herepipe[2], char *eof)
{
	char 	*line;

	while (1)
	{
		line = readline(">");
		if (line == 0)
			break ;
		if (!ft_strcmp(line, eof) || *line == 0)
		{
			free(line);
			break ;
		}
		write(herepipe[1], line, ft_strlen(line));
		write(herepipe[1], "\n", 1);
		free(line);
	}
}

int	heredoc_execute(int herepipe[2], char *eof)
{
	int	pid;
	int	rvalue;

	rvalue = 0;
	pid = fork();
	if (!pid)
	{
		g_is_heredoc = 1;
		write_rl_in_pipe(herepipe, eof);
		exit(0);
	}
	wait(&rvalue);
	return (rvalue);
}

//// echo haha | cat << aaa | grep "h" | wc -l  //, int std_in)
//int	heredoc(t_script *script)
//{
//	t_token *cur;
//	int		hp_dup[2];
//	int		rvalue;
//	int		fnull;

//	rvalue = -1;
//	cur = script->cmd;
//	hp_dup[0] = dup(script->herepipe[0]);
//	fnull = open("/dev/null", O_RDWR);
//	while (cur)
//	{
//		if (cur->type == RD_HEREDOC)
//		{
//			if (rvalue != -1)
//			{
//				dup2(script->herepipe[0], fnull);
//				close(script->herepipe[0]);
//				//close(STDIN_FILENO);
//				//close(script->herepipe[0]);
//				script->herepipe[0] = dup(hp_dup[0]);
//				rvalue = -1;
//			}
//			rvalue = heredoc_excute(script->herepipe, cur->next->content, script->fd_in);
//			if (rvalue != 0)
//			{
//				close(script->herepipe[1]);
//				break ;
//			}
//		}
//		cur = cur->next;
//	}
//	close(script->herepipe[1]);
//	return (rvalue);
//}
