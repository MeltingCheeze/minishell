#include "minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] == s2[i])
            i++;
        else
            break ;
    }
    return (s1[i] - s2[i]);
}

void    check_type(t_token *line)
{
    while (line)
    {
        if (ft_strcmp(line->content, "|") == 0)
        {
            line->type = 'p';
        }
        else if (ft_strcmp(line->content, ">") == 0 || ft_strcmp(line->content, ">>") == 0
            || ft_strcmp(line->content, "<") == 0 || ft_strcmp(line->content, "<<") == 0)
        {
            line->type = 'r';
        }
        else
        {
            line->type = 'w';
        }
        if (line->next)
            line = line->next;
        else
            break;
    }
}

void    check_cmd(t_token *line)
{
    if (line->type == 'w')
        line->type = 'c';
    while (line)
    {
        if (line->type == 'p' && line->next->type == 'w')
            line->next->type = 'c';
        line = line->next;
    }
}

int check_gram(t_token *line)
{
    if (line->type == 'p') //first token
        return (-1);
    while (line)
    {
        if (line->type == 'c' && line->next != NULL) //cmd
        {
            if (line->next->type == 'c')
                return (-1);
        }
        else if (line->type == 'w' && line->next != NULL) //word
        {
            if (line->next->type == 'c')
                return (-1);
        }
        else if (line->type == 'p' && line->next != NULL) //pipe
        {
            if (line->next->type == 'w')
                return (-1);
            else if (line->next->type == 'p')
                return (-1);
        }
        else if (line->type == 'r' == 0 && line->next != NULL) //redir
        {
            if (line->next->type != 'w')
                return (-1);
        }
        if (!line->next && (line->type == 'r' || line->type == 'p')) //last token
            return (-1);
        line = line->next;
    }
    return (0);
}

int    lexcial_analyze(t_token *line)
{
    check_type(line);
    check_cmd(line);
    if (check_gram(line) < 0)
        return (-1);
    return (0);
}

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
	// if (*script == NULL)
	// {
	// 	*script = new;
	// 	return ;
	// }
	last = ft_lstlast(script);
	last->next = new;
}

void    split_cmd(t_token *line)
{
    t_script    *script;
    script = malloc(sizeof(t_script));
    script->cmd = line;
    script->next = NULL;
    t_script    *new;

    while (line)
    {
        if (line->type == 'p')
        {
            new = ft_lstnew(line->next);
            ft_lstadd_back(script, new);
            line->next = NULL;
        }
        line = line->next;
    }
    while (script)
    {
        printf("here\n");
        while (script->cmd)
        {
            printf("%s\n", script->cmd->content);
            script->cmd = script->cmd->next;
        }
        printf("----------\n");
        script->cmd = script->next->cmd;
    }
}