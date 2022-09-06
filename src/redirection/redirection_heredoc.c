#include "redirection.h"
#include "libft.h"

int	heredoc_in_file(int *fd, )
{
	while()
	{
		line = readline();
		if (!ft_strcmp(line, EOF))
		{
			free(line);
			return ;
		}
		new = ft_lstnew(line);
		//if (!new)
		//	ft_error("malloc error(heardoc lst)")
		ft_lstadd_back(&lst, new);
	}
}

int	heredoc_in_buf()
{
	char *line;
	t_list	*lst;
	t_list	*new;

	while()
	{
		line = readline();
		if (!ft_strcmp(line, EOF))
		{
			free(line);
			return ;
		}
		new = ft_lstnew(line);
		//if (!new)
		//	ft_error("malloc error(heardoc lst)")
		ft_lstadd_back(&lst, new);
	}
}

int	heredoc(char *filename, char *EOF)
{
	t_list	*lst;
	int		fd;

	lst = 0;
	if (filename)
		heredoc_in_buf(&lst, EFO);
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
		heredoc_in_file(&fd, filename, EOR);
	}
	if (!fd && !lst)
	return (0);
}
