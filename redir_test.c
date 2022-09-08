//#include "minishell.h"

// O_WRONLY | O_CREAT | O_TRUNC - 쓰기 전용으로 열 때, 파일이 없는 경우 내용을 모두 지우고 파일의 길이를 0으로 변경
//error - invalid access, file not found

//test
#include <unistd.h>
#include <fcntl.h>
#include "lib/libft/libft.h"
#include "include/executor.h"
static int	file_not_found_print(char *cmd, char *filename)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd("No such file or directory", STDERR_FILENO);
	return (1);
}

//int redirection_in(t_script script, char *filepath)
int	rd_in(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (file_not_found_print("cat", filepath));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	rd_out(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	//if (fd == -1)
	//	return (error(filepath));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	rd_append(char *filepath)
{
	int	fd;

	fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
	//if (fd == -1)
	//	return (error(filepath));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
