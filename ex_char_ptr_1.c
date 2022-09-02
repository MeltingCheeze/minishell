#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	void_f(char *s)
{
	s[2] = '1';
}

char	*char_ptr_f(char *s)
{
	s[2] = '1';
	return (s);
}

char	**char_pptr_f(char **s)
{
	(*s)[2] = '1';
	return (s);
}

void	void_free_f(char *s)
{
	free(s);
	s = 0;
}

char	*char_ptr_free_f(char *s)
{
	free(s);
	s = 0;
	return (s);
}

char	**char_pptr_free_f(char **s)
{
	free(*s);
	*s = 0;
	return (s);
}

void	void_pptr_free_f(char **s)
{
	free(*s);
	*s = 0;
}


int	main(void)
{
	char	*s1_alloc;
	char	*s2_alloc;
	char	*s3_alloc;
	char	*s4_alloc;
	char	s1[4];

	s1_alloc = (char *) malloc(sizeof(char) * 4);
	s2_alloc = (char *) malloc(sizeof(char) * 4);
	s3_alloc = (char *) malloc(sizeof(char) * 4);
	s4_alloc = (char *) malloc(sizeof(char) * 4);
	s1[0] = 'a';
	s1[1] = 'b';
	s1[2] = 'c';
	s1[3] = '\0';
	strcpy(s1_alloc, s1);
	strcpy(s2_alloc, s1);
	strcpy(s3_alloc, s1);
	strcpy(s4_alloc, s1);
	void_f(s1_alloc);
	char_ptr_f(s2_alloc);
	char_pptr_f(&s3_alloc);
	printf("void_f : %s\n", s1_alloc);
	printf("char_ptr_f : %s\n", s2_alloc);
	printf("char_pptr_free_f : %s\n", s3_alloc);
	void_free_f(s1_alloc);
	char_ptr_free_f(s2_alloc);
	char_pptr_free_f(&s3_alloc);
	void_pptr_free_f(&s3_alloc);
	printf("void_free_f : %s    %p\n", s1_alloc, s1_alloc);
	printf("char_ptr_free_f : %s   %p\n", s2_alloc, s2_alloc);
	printf("char_pptr_free_f : %s   %p\n", s3_alloc, s3_alloc);
	printf("void_pptr_free_f : %s   %p\n", s3_alloc, s3_alloc);
	void_pptr_free_f(&s4_alloc);
}