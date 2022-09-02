#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s != (unsigned char)c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}

int	main(void)
{
	// printf("%s\n", ft_strchr(" '\"\0", ' '));
	// printf("%s\n", ft_strchr(" '\"\0", 'a'));
	// printf("%s\n", ft_strchr(" '\"\0", '\''));
	// printf("%s\n", ft_strchr(" '\"\0", 'b'));
	// printf("%s\n", ft_strchr(" '\"\0", '"'));
	// printf("%s\n", ft_strchr(" '\"\0", 'c'));
	// printf("%s\n", ft_strchr(" '\"\0", '\0'));
	// printf("%s\n", ft_strchr(" '\"\0", 'd'));

	char	*start = "$";
	int	size;
	size = 1;
	while (ft_strchr("  '\"\0", *(start + size)))
	{
		printf("%d|%s\n", size, (start + size));
		size++;
	}	
	printf("===%d\n", size);
}