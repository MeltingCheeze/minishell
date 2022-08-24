#include "minishell.h"

static char	*find_quote(char **split, int *i, int *j)
{
	char	*q;

	q = 0;
	(*i)--;
	while (!q && split[++(*i)])
	{
		*j = -1;
		while (!q && *(split[*i] + ++(*j)))
		{
			if ((*(split[*i] + *j) == SINGLE) || (*(split[*i] + *j) == DOUBLE))
			{
				q = split[*i] + *j;
				if (*j > 1 && (*(q - 1) == BSLASH) && (*(q - 2) != BSLASH))
					q = 0;
				if (*j == 1 && (*(q - 1) == BSLASH))
					q = 0;
			}
		}
	}
	return (q);
}

static size_t	find_next_quote(char **split, int *i, int *j, char c)
{
	char	*q;
	size_t	size;

	q = 0;
	size = 0;
	(*i)--;
	while (!q && split[++(*i)])
	{
		while (!q && *(split[*i] + ++(*j)))
		{
			size++;
			if (*(split[*i] + *j) == c)
			{
				q = split[*i] + *j;
				if (*j > 1 && (*(q - 1) == BSLASH) && (*(q - 2) != BSLASH))
					q = 0;
				if (*j == 1 && (*(q - 1) == BSLASH))
					q = 0;
			}
		}
		if (!q && *(split[*i] + *j) == 0)
			*j = -1;
	}
	return (size);
}

static char	*join_to_token(char **split, int *i, int *j, char c)
{
	char	*result;
	int		i_start;
	size_t	len;
	size_t	size;

	i_start = *i;
	size = find_next_quote(split, i, j, c);
	size = size + *i - i_start + 2;
	result = (char *)ft_calloc(size, sizeof(char));
	len = 0;
	while (i_start < *i)
	{
		//printf("===%s\n", split[i_start]);
		ft_strlcat(result, split[i_start], size);
		len += ft_strlen(split[i_start]);
		result[len] = ' ';
		result[++len] = '\0';
		i_start++;
	}
	ft_strlcat(result, split[i_start], size);
	len += j;
	result[len] = ' ';
	result[++len] = '\0';
	//printf("i_start == i %s\n", split[i_start]);
	//(*i)++;
	printf("size : %zd len : %zu\n", size, len);
	return (result);
}

static void	make_tokens(t_token **token, char **split)
{
	char	*content;
	char	*quote;
	int		i;
	int		j;
	int		i_start;

	i = 0;
	j = 0;
	while (split[i] && *(split[i] + j))
	{
		i_start = i - 1;
		quote = find_quote(split, &i, &j);
		//printf("i : %d i_start : %d\n", i, i_start);
		while (++i_start < i)
		{
			content = ft_strdup(split[i_start]);
			tokenadd_back(token, tokennew(content));
		}
		if (quote)
		{
			//printf("qutoe: %s\n", quote);
			content = join_to_token(split, &i, &j, *quote);
			tokenadd_back(token, tokennew(content));
		}
		else
		{
			content = ft_strdup(split[i - 1]);
			tokenadd_back(token, tokennew(content));
		}

	}
}

t_token	*tokenizer(char *line)
{
	t_token	*token;
	char	**split;
	t_token	*t;

	split = ft_split(line, ' ');
	if (split == NULL)
		ft_error("ft_split failed : ");
	if (*split == NULL)
		return (NULL);
	token = 0;
	make_tokens(&token, split);
	t = token;
	while (t->next)
	{
		printf("%s\n", t->word);
		t = t->next;
	}
	return (token);
}
