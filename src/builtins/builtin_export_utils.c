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
		while (envp[j + 1])
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

static char	**make_envarr(t_env *env, int env_size)
{
	char	**result;
	size_t	len;
	int		i;

	result = (char **)malloc(sizeof(char *) * (env_size + 1));
	i = 0;
	while (env)
	{
		if (env->value)
			len = ft_strlen(env->key) + ft_strlen(env->value) + 2;
		else
			len = ft_strlen(env->key) + 2; 
		result[i] = (char *)malloc(sizeof(char) * len);
		ft_strcpy(result[i], env->key);
		if (env->value)
		{
			result[i][ft_strlen(env->key)] = '=';
			result[i][ft_strlen(env->key) + 1] = '\0';
			ft_strlcat(result[i], env->value, len);
		}
		i++;
		env = env->next;
	}
	result[i] = 0;
	return (result);
}

void	no_argv_print(t_env_info *env_info)
{
	char	**envarr;
	char	**tmp;
	char	*key;
	char	*value;

	envarr = make_envarr(env_info->head, env_info->size);
	bubble_sort(envarr, env_info->size);
	tmp = envarr;
	while (*(tmp))
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		key = getkey(*tmp);
		ft_putstr_fd(key, STDOUT_FILENO);
		value = getenv(key);
		if (value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(value, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(key);
		tmp++;
	}
}
