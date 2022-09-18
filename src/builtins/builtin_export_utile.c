#include "env.h"
#include "libft.h"
#include "parser.h"

static void	bubble_sort(char **envp, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	no_argv_print(t_env_info *env_info)
{
	char	**envp;
	char	**tmp;

	envp = env_info->envp;
	bubble_sort(envp, env_info->size);
	tmp = envp;
	while (*(tmp))
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(*tmp, STDOUT_FILENO);
		tmp++;
	}
}
