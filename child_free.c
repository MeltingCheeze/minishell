#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	// int		pid;
	char	*s_1;
	char	c;
	int		i;

	s_1 = malloc(sizeof(char) * 11);
	i = -1;
	c = 'a';
	while (++i < 10)
	{
		s_1[i] = c++;
	}
	s_1[i] = 0;
	printf("before fork s_1 : %s\n", s_1);
	if (!fork())
	{
		i = -1;
		c = 'A';
		while (++i < 10)
		{
			s_1[i] = c++;
		}
		s_1[i] = 0;
		printf("C s_1 : %s\n", s_1);
		free(s_1);
		exit(0);
	}
	printf("P s_1 : %s\n", s_1);
}