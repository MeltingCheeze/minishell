#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char *str;

	while (1)
	{
		str = readline("input : "); 
		printf("%s\n", str);
	}
}
