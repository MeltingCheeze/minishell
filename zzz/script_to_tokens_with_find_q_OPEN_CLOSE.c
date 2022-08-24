#include "minishell.h"

static void	find_quote(char **q, const char *line, int *i)
{
	char	*temp;

	q[OPEN] = 0;
	q[CLOSE] = 0;
	while (*(line + *i) && !q[OPEN])
	{
		if (*(line + *i) == SINGLE || *(line + *i) == DOUBLE)
			q[OPEN] = line + *i;
		if ((i > 1 && (*(q[OPEN] - 1) == BSLASH) && (*(q[OPEN] - 2) != BSLASH))
			|| (i == 1 && *(q[OPEN] - 1) == BSLASH))
			q[OPEN] = 0;
		*i++;
	}
	if (q[OPEN])
		temp = q[OPEN];
	while (q[OPEN] && !q[CLOSE])
	{
		q[CLOSE] = ft_strchr(temp + 1, *q[OPEN]);
		if ((*(q[OPEN] - 1) == BSLASH) && (*(q[OPEN] - 2) != BSLASH))
		{
			temp = q[CLOSE];
			q[CLOSE] = 0;
		}
	}
}

static char	**make_token(const char *line)
{
	char	**result;
	char	*quote[2];
	int		i;

	result = ft_split(line, ' ');
	if (result == NULL)
		ft_error("ft_split failed : ");
	i = 0;
	while (*(line + i))
	{
		find_quote(quote, line, &i);
		if (quote[OPEN])

	}
}

void	script_to_tokens(t_token *token, char *line)
{
	char	**token;

	token = make_token(line);
	while ()
}
