#include "minishell.h"

t_script	*ft_lstnew(t_token *token)
{
	t_script	*new;

	new = malloc(sizeof(t_script));
	// if (new == NULL)
		// return (NULL);
	new->cmd = token;
	new->next = NULL;
	return (new);
}

t_script	*ft_lstlast(t_script *script)
{
	if (script == NULL)
		return (script);
	while (script->next != NULL)
		script = script->next;
	return (script);
}

void	ft_lstadd_back(t_script *script, t_script *new)
{
	t_script	*last;

	// if (script == NULL || new == NULL)
	// 	return ;
	if (script == NULL)
	{
		script = new;
		return ;
	}
	last = ft_lstlast(script);
	last->next = new;
}

void    split_cmd(t_token *line)
{
    t_script    *script;
    // script = malloc(sizeof(t_script));
    // script->cmd = line;
    // script->next = NULL; 
    t_script    *new;

    script = 0;
    new = ft_lstnew(line->next);
    ft_lstadd_back(script, new);
    while (line)
    {
        if (line->type == 'p')
        {
            printf("here\n");
            new = ft_lstnew(line->next);
            ft_lstadd_back(script, new);
            line->next = NULL;
        }
        line = line->next;
    }
    script->next = NULL;

    while (script)
    {
        while (script->cmd)
        {
            printf("%s\n", script->cmd->content);
            script->cmd = script->cmd->next;
        }
        printf("----------\n");
        script->cmd = script->next->cmd;
    }
}
