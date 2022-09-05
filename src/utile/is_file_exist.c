#include "struct.h"
#include <sys/stat.h>


t_bool	is_file_exists(char *file_name)
{
	struct stat	buf;

	return (stat(file_name, &buf) == 0);
}