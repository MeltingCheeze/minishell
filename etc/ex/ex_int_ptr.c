#include <stdio.h>

static char	*int_ptr(char **split, int *i, int *j)
{
	char	*quote;

	quote = 0;

	while (!quote && split[*i])
	{
		(*i)++;
		*j = 0;
		while (!quote && *(split[*i] + *j))
		{
			(*j)++;
			printf("i: %d, j %d\n", *i, *j);
			if (*(split[*i] + *j) == '\'' || *(split[*i] + *j) == '"')
				quote = split[*i] + *j;
			if (quote)
			{
				if ((*j > 1 && (*(quote - 1) == '\\') && (*(quote - 2) != '\\'))
					|| (*j == 1 && *(quote - 1) == '\\'))
					quote = 0;
			}
		}
		if (quote)
			(*i)++;
	}
	return (quote);
}

int	main(int argc, char *argv[])
{
	int	i = 0;
	int	j = 0;
	int	k = 0;
	char	*quote;

	while (++k < argc)
		printf("%s\n", argv[k]);
	printf("%d=============\n", k);
	quote = int_ptr(&argv[1], &i, &j);
	printf("i: %d, j %d", i, j);
	if (quote)
		printf("%s", quote);
}
