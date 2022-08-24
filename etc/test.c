#include <stdio.h>

#define LESS "<"
#define GREAT ">"
# define PIPE "|"
# define LESS "<"
# define GRATE ">"
# define DLESS "<<"
# define DGREAT ">>"
# define LESSAND "<&"
# define GREATAND ">&"
# define QMARK "?"
# define DOLLAR "$"
# define SEMICOLON ";"

int	main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;

	//printf("%p %p %p %p %p\n", s1, s2, s3, s4, s5);
	s1 = QMARK;
	s2 = DOLLAR;
	s3 = SEMICOLON;
	s4 = LESSAND;
	s5 = GREATAND;
	//printf("%p %p %p %p %p\n", s1, s2, s3, s4, s5);
	printf("%s %s %s %s %s\n", s1, s2, s3, s4, s5);
}
