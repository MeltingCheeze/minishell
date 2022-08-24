static void	make_tokens(t_token **token, char *line)
{
	char	*quote;
	char	*delim;
	int		n;

	n = 0;
	while (line && *line)
	{
		quote = find_quote(line);
		delim = ft_strchr(line, SPACE);
		if (quote)
		{
			while (delim && (delim < quote))
			{
				line = add_token(token, line, delim, n);
				delim = ft_strchr(delim + 1, SPACE);
				n++;
			}
			line = extend_token(token, line, quote, n);
			n++;
		}
		else
		{
			while (delim)
			{
				line = add_token(token, line, delim, n);
				delim = ft_strchr(delim + 1, SPACE);
				n++;
			}
			tokenadd_back(token, tokennew(ft_strdup(line), n, SPACE));
			line = 0;
			printf("5");

		}
	}
}
