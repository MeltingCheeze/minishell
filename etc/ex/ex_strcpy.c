#include <stdlib.h>
#include <string.h>

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i	= 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	main(int argc, char *argv[])
{
	char	**words;
	char	*result;
	char	*dest;
	int		i;
	int		j;
	int		size;

	size = 30;
	i = 0;
	j = 0;
	words = &argv[1];
	result = (char *)malloc(size + argc);
	while (i < argc)
	{
		dest = ft_strcpy_size(result , words[i + 1])

	}
}
