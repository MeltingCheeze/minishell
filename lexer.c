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

