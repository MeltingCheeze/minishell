#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include "../../lib/libft/libft.h"

#define SINGLE '\''
#define DOUBLE '"'
#define BSLASH '\\'

static char	*check_quotes(char *line, int *has)
{
	static char *quote = 0;

	if (*has == 0)
		quote = 0;
	if (*line == SINGLE && *has == 0)
	{
		*has += SINGLE;
		quote = line;
	}
	else if (*line == SINGLE && *has == SINGLE)
		*has -= SINGLE;
	else if (*line == SINGLE && *has == DOUBLE)
		;
	else if (*line == DOUBLE && *has == 0)
	{
		*has += DOUBLE;
		quote = line;
	}
	else if (*line == DOUBLE && *has == SINGLE)
		;
	else if (*line == DOUBLE && *has == DOUBLE && *(line - 1) != '\\')
		*has -= DOUBLE;
	return (quote);
}

//static char	*alloc_token(const char *s1, size_t n, char **quote)
//{
//	char	*result;
//	size_t	i;
//	size_t	cnt;

//	result = (char *)malloc(sizeof(char) * (n + 1));
//	if (!result)
//	{
//		perror("malloc error(token) : ");
//		exit(1);
//	}
//		//ft_error("malloc error(token) : ");
//	i = -1;
//	cnt = -1;
//	while (++i < n)
//	{
//		if ((*quote == 0) && (s1[i] != BSLASH
//				|| (s1[i] == BSLASH && s1[i + 1] == BSLASH)))
//			result[++cnt] = s1[i];
//		if (*quote)
//		{
//			//if ((**quote == SINGLE) && (s1[i] != **quote))
//			//	result[++cnt] = s1[i];
//			//else if ((**quote == DOUBLE) && (s1[i] != **quote))
//			//	result[++cnt] = s1[i];
//			result[++cnt] = s1[i];
//			if ((**quote == DOUBLE) && ((s1[i] == BSLASH) && s1[i + 1] == DOUBLE))
//					result[++cnt] = s1[i + 1];
//		}
//	}
//	while (cnt < n)
//		result[cnt++] = '\0';
//	return (result);
//}

static char	*alloc_token(const char *s1, size_t n, char **quote)
{
	char	*result;
	size_t	i;
	size_t	cnt;

	result = (char *)malloc(sizeof(char) * (n + 1));
	if (!result)
	{
		printf("malloc error(token) : ");
		exit(1);
	}
	i = -1;
	cnt = -1;
	while (++i < n)
	{
		if ((*quote == 0) &&
				(s1[i] != BSLASH || (s1[i] == BSLASH && s1[i + 1] == BSLASH)))
			result[++cnt] = s1[i];
		if (*quote)
		{
			if ((**quote == SINGLE) && (s1[i] != **quote))
				result[++cnt] = s1[i];
			if ((**quote == DOUBLE) && (s1[i] != **quote))
				result[++cnt] = s1[i];
			else if ((**quote == DOUBLE) && ((s1[i] == BSLASH) && s1[i + 1] == DOUBLE))
				result[++cnt] = s1[i + 1];
		}
	}
	while (cnt < n)
		result[++cnt] = '\0';
	return (result);
}

void	line_to_token(char *line)
{
	char	*delim;
	char	*quote;
	int		has;
	int		i;
	char	*token;

	while (*line && (*line == ' '))
		line++;
	while (*line)
	{
		has = 0;
		delim = 0;
		quote = 0;
		while (!delim && !quote)
		{
			delim = ft_strchr(line, ' ');
			printf("space : %ldth\n", delim - line);
			i = -1;
			while (++i < delim - line)
				quote = check_quotes(line + i, &has);
			printf("has : %d  quote : %s \n", has, quote);
			if (quote && has)
				delim = ft_strchr(quote + 1, *quote);
		}
		printf("n : %ld, quote : %s, delim : %s|\n", delim - line, quote, delim - 1);
		token = alloc_token(line, delim - line + 1, &quote);
		printf("%s\n", token);
		//printf("%c\n", *token);
		free(token);
		line = delim + 1;
		while (*line && (*line == ' '))
			line++;
	}
}

char	*ft_readline(void)
{
	char *line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("token>");
	if (line)
		add_history(line);
	return (line);
}

int	main(void)
{
	char	*line;
	char	*script;

	while (42)
	{
		line = ft_readline();
		if (__sfeof(stdin))
			exit(0);
		script = ft_strjoin(line, " ");
		line_to_token(script);
		free(line);
		free(script);
	}
}
