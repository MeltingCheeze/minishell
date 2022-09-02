#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	char_ptr_f(char *s)
{
	s = (char *) malloc(sizeof(char) * 4);
}

void	char_pptr_f(char **s)
{
	*s = (char *) malloc(sizeof(char) * 4);
}

int	main(void)
{
	char	*s1_alloc;
	char	*s2_alloc;
	char	s1[4];

	s1_alloc = (char *) malloc(sizeof(char) * 4);
	s2_alloc = (char *) malloc(sizeof(char) * 4);
	s1[0] = 'a';
	s1[1] = 'b';
	s1[2] = 'c';
	s1[3] = '\0';
	strcpy(s1_alloc, s1);
	strcpy(s2_alloc, s1);
	printf("s1 : %s    %p\n", s1_alloc, s1_alloc);
	printf("s2 : %s    %p\n", s2_alloc, s2_alloc);
	char_ptr_f(s1_alloc);
	char_pptr_f(&s2_alloc);
	printf("s1 : %s    %p\n", s1_alloc, s1_alloc);
	printf("s2 : %s    %p\n", s2_alloc, s2_alloc);

}