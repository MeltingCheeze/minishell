char	set_quote(char old_quote, char new_quote)
{
	if (!old_quote)
		return (new_quote);
	if (old_quote && (old_quote == new_quote))
		return (0);
	return (old_quote);
}