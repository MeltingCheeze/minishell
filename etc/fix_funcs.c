	char	*quote_2;
	char	*delim;
	int		is_first;

	is_first = 1;
	delim = ft_strchr(line, SPACE);
	while (line && *line && (is_first || *(line - 1) != SPACE))
	{
		if (is_first == 1)
			is_first = 0;
		if (quote_1)
			quote_2 = find_quote(quote_1 + 1);
		if ((!quote_1 && delim)
				|| (quote_1 && (delim && (delim < quote_1))))
			line = add_token(token, line, delim, n);
		else if ((quote_1 && !delim)
				|| (quote_1 && (delim && (delim > quote_1))))
			line = add_token(token, line, quote_2, n);
		quote_1 = find_quote(line);
		delim = ft_strchr(line, SPACE);
		if (*line && !quote_1 && !delim)
		{
			tokenadd_back(token, tokennew(ft_strdup(line), n, SPACE));
			line = 0;
		}
	}
	return (line);
